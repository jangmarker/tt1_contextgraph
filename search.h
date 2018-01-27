#ifndef TT1_CONTEXTGRAPH_SEARCH_H
#define TT1_CONTEXTGRAPH_SEARCH_H

#include "vector.h"
#include "database.h"

#include <memory>

namespace search {
    template<typename ValueType>
    struct Named {
        explicit Named(ValueType value) : value(value)
        { }
        operator ValueType() { return value; };
        ValueType value;
    };

    struct Depth : public Named<std::size_t> {
        explicit Depth(std::size_t depth) : Named(depth) { }
    };
    struct NeighborCount : public Named<std::size_t> {
        explicit NeighborCount(std::size_t count) : Named(count) { }
    };

    class SearchResult;
    using SearchResultPtr = std::unique_ptr<SearchResult>;
    using Neighbors = std::vector<SearchResultPtr>;
    struct SearchResult {
        SearchResult(std::string_view word, Neighbors&& neighbors);
        Word word;
        Neighbors neighbors;
    };

    SearchResultPtr search(const Database& db, const Word& word, NeighborCount neighborCount, Depth depth);
};


#endif //TT1_CONTEXTGRAPH_SEARCH_H
