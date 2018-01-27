#ifndef TT1_CONTEXTGRAPH_HELPER_TST_H
#define TT1_CONTEXTGRAPH_HELPER_TST_H

#include "vector.h"
#include "database.h"

Vector make_vector(std::string_view word, std::initializer_list<double> values);
Database make_database_3();

#endif //TT1_CONTEXTGRAPH_HELPER_TST_H
