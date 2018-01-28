#include "search.h"

search::SearchResult::SearchResult(std::string_view word, search::Neighbors&& neighbors)
    : word(word)
    , neighbors(std::move(neighbors))
{

}


search::SearchResultPtr search::search(const Database& db, WordView word, NeighborCount neighborCount, Depth depth)
{
    if (depth == 0) {
        return std::make_unique<SearchResult>(word, Neighbors{});
    } else {
        auto res = std::make_unique<SearchResult>(word, Neighbors{});
        res->neighbors.reserve(neighborCount);
        auto neighborWords = db.most_similar(word, neighborCount);
        for (WordView neighborWord : neighborWords) {
            auto neighbor = search(db, neighborWord, neighborCount, Depth{depth - 1});
            res->neighbors.push_back(std::move(neighbor));
        }
        return res;
    }

}