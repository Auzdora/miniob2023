#include "globals.h"
#include "sql/expr/tuple.h"

Tuple *parent_tuple = nullptr;
Tuple *sub_select_tuple = nullptr;
JoinedTuple *top_tuple = new JoinedTuple;
std::vector<Tuple *> sub_queries_tuple;
int level = 0;

void clear_global_tuple() {
    if (top_tuple->get_right() != nullptr)
    {
        JoinedTuple *temp = &(*(static_cast<JoinedTuple *>(top_tuple->get_right())));
        top_tuple->set_left(nullptr);
        delete top_tuple;
        top_tuple = temp;
    }
//     parent_tuple = nullptr;
//     sub_select_tuple = nullptr;
}