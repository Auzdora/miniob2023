#include "globals.h"
#include "sql/expr/tuple.h"

Tuple *parent_tuple = nullptr;
Tuple *sub_select_tuple = nullptr;
JoinedTuple *join_tuple = new JoinedTuple;

void clear_global_tuple() {
    parent_tuple = nullptr;
    sub_select_tuple = nullptr;
}