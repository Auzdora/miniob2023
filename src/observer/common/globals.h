#ifndef GLOBALS_H
#define GLOBALS_H

#include "sql/expr/tuple.h"
extern Tuple *parent_tuple;
extern Tuple *sub_select_tuple;
extern JoinedTuple *join_tuple;

void clear_global_tuple();
#endif
