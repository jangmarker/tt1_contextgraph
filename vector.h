#ifndef TT1_CONTEXTGRAPH_VECTOR_H
#define TT1_CONTEXTGRAPH_VECTOR_H

#include <string>
#include <vector>

using Word = std::string;
using WordView = std::string_view;

struct Vector {
    explicit Vector(std::size_t valueCount);

    Word word;
    std::vector<double> values;
    double euclideanNorm;
};

bool operator==(const Vector& lhs, const Vector& rhs);

#endif //TT1_CONTEXTGRAPH_VECTOR_H
