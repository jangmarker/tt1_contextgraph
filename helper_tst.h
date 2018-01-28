#ifndef TT1_CONTEXTGRAPH_HELPER_TST_H
#define TT1_CONTEXTGRAPH_HELPER_TST_H

#include <ostream>
#include <sstream>
#include <iterator>

#include "vector.h"
#include "database.h"
#include "search.h"

Vector make_vector(std::string_view word, std::initializer_list<double> values);
Database make_database_3();

// base case
void append_neighbor(search::Neighbors* neighbors) { }

template<typename Arg, typename... Args>
void append_neighbor(search::Neighbors* neighbors, Arg&& arg, Args&&... args) {
    neighbors->push_back(std::forward<Arg>(arg));
    append_neighbor(neighbors, std::forward<Args>(args)...);
}

template<typename... Args>
search::Neighbors make_neighbors(Args&&... args) {
    search::Neighbors neighbors;
    neighbors.reserve(sizeof...(args));
    append_neighbor(&neighbors, std::forward<Args>(args)...);
    return neighbors;
}

search::SearchResultPtr make_searchresult(std::string_view name, search::Neighbors&& neighbors = {}) {
    return std::make_unique<search::SearchResult>(name, std::move(neighbors));
}

std::string read(std::stringstream& stream) {
    return std::string{std::istreambuf_iterator<char>(stream), {}};
}

#endif //TT1_CONTEXTGRAPH_HELPER_TST_H
