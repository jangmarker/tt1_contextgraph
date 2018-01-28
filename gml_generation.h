#ifndef TT1_CONTEXTGRAPH_GML_GENERATION_H
#define TT1_CONTEXTGRAPH_GML_GENERATION_H

#include "search.h"

#include <ostream>

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

    std::ostream& operator<<(std::ostream& stream, search::SearchResultPtr& root);
    std::ostream& operator<<(std::ostream& stream, const Edge& edge);
    std::ostream& operator<<(std::ostream& stream, const Node& node);
};


#endif //TT1_CONTEXTGRAPH_GML_GENERATION_H
