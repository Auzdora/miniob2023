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
// Created by WangYunlai on 2022/6/27.
//

#include "common/log/log.h"
#include "sql/operator/predicate_physical_operator.h"
#include "storage/record/record.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/field/field.h"

PredicatePhysicalOperator::PredicatePhysicalOperator(std::unique_ptr<Expression> expr) : expression_(std::move(expr))
{
  ASSERT(expression_->value_type() == BOOLEANS, "predicate's expression should be BOOLEAN type");
}

PredicatePhysicalOperator::PredicatePhysicalOperator(std::unique_ptr<Expression> expr,std::vector<std::string> subselect_expr_names){
  expression_ = std::move(expr);
  ASSERT(expression_->value_type() == BOOLEANS, "predicate's expression should be BOOLEAN type");
  if (!subselect_expr_names.empty())
    subselect_expr_names_.swap(subselect_expr_names);
}

RC PredicatePhysicalOperator::open(Trx *trx)
{
  if (children_.size() < 1) {
    LOG_WARN("predicate operator must has one child");
    return RC::INTERNAL;
  }
  trx_ = trx;
  return children_[0]->open(trx);
}

RC PredicatePhysicalOperator::next()
{
  RC rc = RC::SUCCESS;
  PhysicalOperator *oper = children_.front().get();

  while (RC::SUCCESS == (rc = oper->next())) {
    Tuple *tuple = oper->current_tuple();
    if (nullptr == tuple) {
      rc = RC::INTERNAL;
      LOG_WARN("failed to get tuple from operator");
      break;
    }

    Value value;

    /// 有子查询的情况
    if (children_.size() > 1)
    {
      switch (expression_->type())
      {
      case ExprType::COMPARISON:
        {
          rc = do_compare_expr(*tuple,value);
          if (rc != RC::SUCCESS)
            return rc;
        }
        break;
      case ExprType::CONJUNCTION:
        {
          ConjunctionExpr * top = static_cast<ConjunctionExpr *>(expression_.get());
          std::vector<std::unique_ptr<Expression>> &children = top->children();
          bool result = false;
          for(int i = 0; i < children.size();i++){
            switch (children[i]->type())
            {
            case ExprType::COMPARISON:
             {
              rc = do_compare_expr(*tuple,value);
              if (rc != RC::SUCCESS)
                return rc;
              if (!value.get_boolean())
                return rc;
             } break;
            default:
              return RC::INTERNAL;
              break;
            }
          }
        }
        break;
      default:
        break;
      }
    }
    else
      rc = expression_->get_value(*tuple, value);
    if (rc != RC::SUCCESS) {
      return rc;
    }

    if (value.get_boolean()) {
      return rc;
    }
  }
  return rc;
}

RC PredicatePhysicalOperator::close()
{
  children_[0]->close();
  return RC::SUCCESS;
}

Tuple *PredicatePhysicalOperator::current_tuple()
{
  return children_[0]->current_tuple();
}

RC PredicatePhysicalOperator::do_compare_expr(Tuple &tuple,Value &value){
  ComparisonExpr *top = static_cast<ComparisonExpr*>(expression_.get());
  int left_sub_id = 0;
  int right_sub_id = 0;
  // 查找左子查询的位置
  if (top->left()->type() == ExprType::SUBSELECT)
  {
    std::string left_expr_name = top->left()->name();
    auto it = find(subselect_expr_names_.begin(),subselect_expr_names_.end(),left_expr_name);
    if (it != subselect_expr_names_.end())
      left_sub_id = it-subselect_expr_names_.begin() + 1;
    else
      return RC::INTERNAL;
  }
  // 查找右子查询的位置
  if (top->right()->type() == ExprType::SUBSELECT)
  {
    std::string right_expr_name = top->right()->name();
    auto it = find(subselect_expr_names_.begin(),subselect_expr_names_.end(),right_expr_name);
    if (it != subselect_expr_names_.end())
      right_sub_id = it-subselect_expr_names_.begin() + 1;
    else
      return RC::INTERNAL;
  }

  if (left_sub_id == 0 && right_sub_id == 0)
    return RC::INTERNAL;
  RC rc = RC::SUCCESS;
  PhysicalOperator *left_suboper = nullptr;
  PhysicalOperator *right_suboper = nullptr;
  Value left_value;
  Value right_value;
  switch (top->comp())
  {
  case IN_OP:
    {
      // if (left_sub_id != 0)
      // {
      //   if (RC::SUCCESS != (rc = children_[left_sub_id]->open(trx_)))
      //       return rc;
      //   left_suboper = children_[left_sub_id].get();
        
      // }else{
      //   top->left()->get_value(tuple,left_value);
      // }
      top->left()->get_value(tuple,left_value);
      if (right_sub_id != 0)
      {
        if (RC::SUCCESS != (rc = children_[right_sub_id]->open(trx_)))
            return rc;
        right_suboper = children_[right_sub_id].get();
        rc = InOpFunc(right_suboper,left_value,value,top->comp());
        if (rc == RC::INTERNAL)
        {
          right_suboper->close();
          return rc;
        }
        rc = right_suboper->close();
        return rc;
      }else{
        return RC::INTERNAL;
      }
      
    }
    break;
  case NOT_IN_OP:
    {
      top->left()->get_value(tuple,left_value);
      if (right_sub_id != 0)
      {
        if (RC::SUCCESS != (rc = children_[right_sub_id]->open(trx_)))
            return rc;
        right_suboper = children_[right_sub_id].get();
        rc = InOpFunc(right_suboper,left_value,value,top->comp());
        if (rc == RC::INTERNAL)
        {
          right_suboper->close();
          return rc;
        }
        rc = right_suboper->close();
        return rc;
      }else{
        return RC::INTERNAL;
      }
    }
    break;
  case EXISTS_OP:
    {
      top->left()->get_value(tuple,left_value);
      if (right_sub_id != 0)
      {
        if (RC::SUCCESS != (rc = children_[right_sub_id]->open(trx_)))
            return rc;
        right_suboper = children_[right_sub_id].get();
        if (RC::SUCCESS == (rc =  right_suboper->next()))
        {
          Tuple *tuple =  right_suboper->current_tuple();
          if (nullptr == tuple) {
            rc = RC::INTERNAL;
            LOG_WARN("failed to get tuple from operator");
            return rc;
          }
          value.set_boolean(true);
        }
        else
        {
          value.set_boolean(false);
        }
        rc = right_suboper->close();
        return rc;
      }else{
        return RC::INTERNAL;
      }
    }break;
  case NOT_EXISTS_OP:
    {
      top->left()->get_value(tuple,left_value);
      if (right_sub_id != 0)
      {
        if (RC::SUCCESS != (rc = children_[right_sub_id]->open(trx_)))
            return rc;
        right_suboper = children_[right_sub_id].get();
        if (RC::SUCCESS == (rc =  right_suboper->next()))
        {
          Tuple *tuple =  right_suboper->current_tuple();
          if (nullptr == tuple) {
            rc = RC::INTERNAL;
            LOG_WARN("failed to get tuple from operator");
            return rc;
          }
          value.set_boolean(false);             // aggr 返回tuple 但是value数量为0 没做判断
        }
        else
        {
          value.set_boolean(true);
        }
        rc = right_suboper->close();
        return rc;
      }else{
        return RC::INTERNAL;
      }
    }break;
  default:
    {
      // 获取左边的值
      if (left_sub_id != 0)
      {
        if (RC::SUCCESS != (rc = children_[left_sub_id]->open(trx_)))
            return rc;
        left_suboper = children_[left_sub_id].get();
        if (RC::SUCCESS == (rc = left_suboper->next()))
        {
          Tuple *tuple = left_suboper->current_tuple();
          if (nullptr == tuple) {
            rc = RC::INTERNAL;
            LOG_WARN("failed to get tuple from operator");
            return rc;
          }
          if (tuple->cell_num() != 1)
          {
            if (tuple->cell_num() == 0){
              left_value.set_null();
            }
            else{
              return RC::INTERNAL;
            }
          }else{
            tuple->cell_at(0,left_value);
          }

          // 有多个值
          if (RC::SUCCESS  == left_suboper->next())
            return RC::INTERNAL;
        }else{
          // 没有值  返回null
          left_value.set_null();
        }

      }else{
        top->left()->get_value(tuple,left_value);
      }

      // 获取右边的值
      if (right_sub_id != 0)
      {
        if (RC::SUCCESS != (rc = children_[right_sub_id]->open(trx_)))
            return rc;
        right_suboper = children_[right_sub_id].get();
        if (RC::SUCCESS == (rc = right_suboper->next()))
        {
          Tuple *tuple = right_suboper->current_tuple();
          if (nullptr == tuple) {
            rc = RC::INTERNAL;
            LOG_WARN("failed to get tuple from operator");
            return rc;
          }
          if (tuple->cell_num() != 1)
          {
            if (tuple->cell_num() == 0){
              right_value.set_null();
            }else{
              return RC::INTERNAL;
            }
          }else{
            tuple->cell_at(0,right_value);
          }

          // 有多个值
          if (RC::SUCCESS  == right_suboper->next())
            return RC::INTERNAL;
        }else{
          // 没有值  返回null
          right_value.set_null();
        }

      }else{
        top->right()->get_value(tuple,right_value);
      }
      if(left_value.compare(right_value,top->comp()))
        value.set_boolean(true);
      else 
        value.set_boolean(false);
      if(left_sub_id)
        rc = left_suboper->close();
      if(right_sub_id)
        rc = right_suboper->close();
      return rc;
    }
    break;
  }

}

RC PredicatePhysicalOperator::InOpFunc(PhysicalOperator *&child,Value &left_value,Value &value, CompOp comp){
  RC rc;
  while (RC::SUCCESS == (rc = child->next()))
  {
    Tuple *tuple = child->current_tuple();
    if (nullptr == tuple) {
      rc = RC::INTERNAL;
      LOG_WARN("failed to get tuple from operator");
      return rc;
    }
    // 子查询只能返回的tuple包含一个value
    if (tuple->cell_num() != 1)
    {
      if (tuple->cell_num() == 0){
        continue;
      }
      return RC::INTERNAL;
    } 
    Value cell;
    tuple->cell_at(0,cell);
    if (comp == IN_OP)
    {
      if (left_value.compare(cell,comp))
      {
        value.set_boolean(true);
        return RC::SUCCESS;
      }
    } else
    {
      if (left_value.compare(cell,IN_OP))
      {
        value.set_boolean(false);
        return RC::SUCCESS;
      }
    }
      

  }
  if (comp == IN_OP)
    value.set_boolean(false);
  else
    value.set_boolean(true);
  if (rc ==RC::RECORD_EOF)
    rc = RC::SUCCESS;
  return rc; 
}
