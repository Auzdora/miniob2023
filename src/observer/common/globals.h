#ifndef GLOBALS_H
#define GLOBALS_H

#include "sql/expr/tuple.h"
extern Tuple *parent_tuple;
extern Tuple *sub_select_tuple;
extern std::vector<Tuple *> sub_queries_tuple;
extern JoinedTuple *top_tuple;
extern int level;

void clear_global_tuple();
#endif
