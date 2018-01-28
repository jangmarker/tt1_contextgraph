#ifndef TT1_CONTEXTGRAPH_GML_GENERATION_H
#define TT1_CONTEXTGRAPH_GML_GENERATION_H

#include "search.h"

#include <ostream>
#include <experimental/filesystem>

namespace gml_generation
{
    struct Edge {
        std::string_view source;
        std::string_view target;
    };
    bool operator<(const Edge& lhs, const Edge& rhs);

    struct Node {
        explicit Node(std::string_view l);
        std::string_view label;
    };
    bool operator<(const Node& lhs, const Node& rhs);

    struct Graph {
        search::SearchResultPtr& root;
        std::size_t depth;
    };

    std::ostream& operator<<(std::ostream& stream, const gml_generation::Graph& graph);
    std::ostream& operator<<(std::ostream& stream, const Edge& edge);
    std::ostream& operator<<(std::ostream& stream, const Node& node);

    void writeToFile(const std::experimental::filesystem::path& path, const gml_generation::Graph& root);
};


#endif //TT1_CONTEXTGRAPH_GML_GENERATION_H
