/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by WangYunlai on 2022/12/30.
//

#include "sql/operator/join_physical_operator.h"

NestedLoopJoinPhysicalOperator::NestedLoopJoinPhysicalOperator()
{}

RC NestedLoopJoinPhysicalOperator::open(Trx *trx)
{
  if (children_.size() != 2) {
    LOG_WARN("nlj operator should have 2 children");
    return RC::INTERNAL;
  }

  RC rc = RC::SUCCESS;
  left_ = children_[0].get();
  right_ = children_[1].get();
  right_closed_ = true;
  round_done_ = true;

  rc = left_->open(trx);
  trx_ = trx;
  return rc;
}

RC NestedLoopJoinPhysicalOperator::next()
{
  bool left_need_step = (left_tuple_ == nullptr);
  RC rc = RC::SUCCESS;
  if (round_done_) {
    left_need_step = true;
  } else {
    rc = right_next();
    if (rc != RC::SUCCESS) {
      if (rc == RC::RECORD_EOF) {
        left_need_step = true;
      } else {
        return rc;
      }
    } else {
      return rc;  // got one tuple from right
    }
  }

  if (left_need_step) {
    rc = left_next();
    if (rc != RC::SUCCESS) {
      return rc;
    }
  }

  rc = right_next();
  return rc;
}

RC NestedLoopJoinPhysicalOperator::close()
{
  RC rc = left_->close();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to close left oper. rc=%s", strrc(rc));
  }

  if (!right_closed_) {
    rc = right_->close();
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to close right oper. rc=%s", strrc(rc));
    } else {
      right_closed_ = true;
    }
  }
  return rc;
}

Tuple *NestedLoopJoinPhysicalOperator::current_tuple()
{
  return &joined_tuple_;
}

RC NestedLoopJoinPhysicalOperator::left_next()
{
  RC rc = RC::SUCCESS;
  rc = left_->next();
  if (rc != RC::SUCCESS) {
    return rc;
  }

  left_tuple_ = left_->current_tuple();
  joined_tuple_.set_left(left_tuple_);
  return rc;
}

RC NestedLoopJoinPhysicalOperator::right_next()
{
  RC rc = RC::SUCCESS;
  if (round_done_) {
    if (!right_closed_) {
      rc = right_->close();
      right_closed_ = true;
      if (rc != RC::SUCCESS) {
        return rc;
      }
    }

    rc = right_->open(trx_);
    if (rc != RC::SUCCESS) {
      return rc;
    }
    right_closed_ = false;

    round_done_ = false;
  }

  rc = right_->next();
  if (rc != RC::SUCCESS) {
    if (rc == RC::RECORD_EOF) {
      round_done_ = true;
    }
    return rc;
  }

  right_tuple_ = right_->current_tuple();
  joined_tuple_.set_right(right_tuple_);
  return rc;
}

BlockNestedLoopJoinPhysicalOperator::BlockNestedLoopJoinPhysicalOperator()
    : PhysicalOperator() {}

RC BlockNestedLoopJoinPhysicalOperator::open(Trx *trx) {
    trx_ = trx;
    RC rc = left_->open(trx);
    if (rc != RC::SUCCESS) {
        return rc;
    }
    rc = right_->open(trx);
    if (rc != RC::SUCCESS) {
        return rc;
    }
    return load_next_block();  // Load the first block upon opening
}

RC BlockNestedLoopJoinPhysicalOperator::load_next_block() {
    left_block_.clear();
    current_tuple_idx_ = 0;
    RC rc = RC::SUCCESS;
    while (left_block_.size() < BLOCK_SIZE_) {
        rc = left_->next();
        if (rc == RC::RECORD_EOF) {
            break;
        } else if (rc != RC::SUCCESS) {
            return rc;
        }
        left_block_.push_back(left_->current_tuple());
    }
    return rc;
}

RC BlockNestedLoopJoinPhysicalOperator::left_next() {
    if (current_tuple_idx_ < left_block_.size()) {
        left_tuple_ = left_block_[current_tuple_idx_++];
        joined_tuple_.set_left(left_tuple_);
        return RC::SUCCESS;
    } else {
        return load_next_block();
    }
}

RC BlockNestedLoopJoinPhysicalOperator::right_next() {
    RC rc = right_->next();
    if (rc != RC::SUCCESS) {
        return rc;
    }
    right_tuple_ = right_->current_tuple();
    joined_tuple_.set_right(right_tuple_);
    return RC::SUCCESS;
}

RC BlockNestedLoopJoinPhysicalOperator::next() {
    RC rc = RC::SUCCESS;
    while (true) {
        if (round_done_) {
            rc = left_next();
            if (rc != RC::SUCCESS) {
                return rc;
            }
            round_done_ = false;
        }
        rc = right_next();
        if (rc == RC::RECORD_EOF) {
            round_done_ = true;
            right_->close();  // Close the inner relation
            right_->open(trx_);  // Reopen to start from the beginning
        } else {
            return rc;
        }
    }
}

RC BlockNestedLoopJoinPhysicalOperator::close() {
    RC rc1 = left_->close();
    RC rc2 = right_->close();
    return (rc1 == RC::SUCCESS && rc2 == RC::SUCCESS) ? RC::SUCCESS : RC::INTERNAL;
}

Tuple* BlockNestedLoopJoinPhysicalOperator::current_tuple() {
    return &joined_tuple_;
}
