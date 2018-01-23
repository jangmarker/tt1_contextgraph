#include "vector.h"

Vector::Vector(std::size_t valueCount)
{
    values.reserve(valueCount);
}

bool operator==(const Vector& lhs, const Vector& rhs)
{
    return lhs.word == rhs.word;
}
