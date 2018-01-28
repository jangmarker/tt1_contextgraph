#include "gml_generation.h"

#include <set>
#include <stack>

namespace {
    using namespace gml_generation;

    void createEdgesNodes(search::SearchResultPtr& root, std::set<Edge>* edges, std::set<Node>* nodes)
    {
        nodes->emplace(root->word);
        for (auto& neighbor : root->neighbors) {
            edges->emplace(Edge{root->word, neighbor->word});
            createEdgesNodes(neighbor, edges, nodes);
        }
    }
}

Node::Node(std::string_view l)
        : label(l)
{ }

bool gml_generation::operator<(const gml_generation::Edge& lhs, const gml_generation::Edge& rhs)
{
    return lhs.source == rhs.source ? lhs.target < rhs.target : lhs.source < rhs.source;
}

bool gml_generation::operator<(const gml_generation::Node& lhs, const gml_generation::Node& rhs)
{
    return lhs.label < rhs.label;
}

std::ostream& gml_generation::operator<<(std::ostream& stream, search::SearchResultPtr& root)
{
    std::set<Edge> edges;
    std::set<Node> nodes;

    createEdgesNodes(root, &edges, &nodes);


    stream << "graph [" << std::endl;
    stream << "  directed 0" << std::endl;
    for (const auto& node : nodes) {
        stream << node;
    }
    for (const auto& edge : edges) {
        stream << edge;
    }
    stream << "]" << std::endl;

    return stream;
}

std::ostream& gml_generation::operator<<(std::ostream& stream, const Edge& edge)
{
    stream << "  edge [" << std::endl;
    stream << "    source \"" << edge.source << '"' << std::endl;
    stream << "    target \"" << edge.target << '"' << std::endl;
    stream << "  ]" << std::endl;

    return stream;
}

std::ostream& gml_generation::operator<<(std::ostream& stream, const Node& node)
{
    stream << "  node [" << std::endl;
    stream << "    id \"" << node.label << '"' << std::endl;
    stream << "    label \"" << node.label << '"' << std::endl;
    stream << "  ]" << std::endl;

    return stream;
}