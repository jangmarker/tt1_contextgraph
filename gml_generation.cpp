#include "gml_generation.h"

#include <set>
#include <stack>
#include <string_view>
#include <fstream>

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

    std::set<Node> createNodes(search::SearchResultPtr& root, std::size_t depth)
    {
        std::set<Node> nodes;
        nodes.emplace(root->word);
        if (depth > 0) {
            for (auto& neighbor : root->neighbors) {
                nodes.merge(createNodes(neighbor, depth - 1));
            }
        }
        return nodes;
    }

    std::set<Edge> createEdges(search::SearchResultPtr& root, const std::set<Node>& nodes, std::size_t depth)
    {
        std::set<Edge> edges;
        for (auto& neighbor : root->neighbors) {
            if (depth > 0 || nodes.find(Node{neighbor->word}) != nodes.end()) {
                edges.emplace(Edge{root->word, neighbor->word});
            }
            edges.merge(createEdges(neighbor, nodes, depth - 1));
        }
        return edges;

    }
}

Node::Node(std::string_view l)
        : label(l)
{ }

bool gml_generation::operator<(const gml_generation::Edge& lhs, const gml_generation::Edge& rhs)
{
    std::string_view rhsLower = rhs.source < rhs.target ? rhs.source : rhs.target;
    std::string_view rhsHigher = rhs.source < rhs.target ? rhs.target : rhs.source;
    std::string_view lhsLower = lhs.source < lhs.target ? lhs.source : lhs.target;
    std::string_view lhsHigher = lhs.source < lhs.target ? lhs.target : lhs.source;
    return lhsLower == rhsLower ? lhsHigher < rhsHigher : lhsLower < rhsLower;
}

bool gml_generation::operator<(const gml_generation::Node& lhs, const gml_generation::Node& rhs)
{
    return lhs.label < rhs.label;
}

std::ostream& gml_generation::operator<<(std::ostream& stream, const gml_generation::Graph& graph)
{
    std::set<Node> nodes = createNodes(graph.root, graph.depth);
    std::set<Edge> edges = createEdges(graph.root, nodes, graph.depth);

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

void gml_generation::writeToFile(const std::experimental::filesystem::path& path, const gml_generation::Graph& graph)
{
    std::ofstream stream(path);
    stream << graph;
}
