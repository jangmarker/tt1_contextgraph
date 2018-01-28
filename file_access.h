#ifndef TT1_CONTEXTGRAPH_FILE_ACCESS_H
#define TT1_CONTEXTGRAPH_FILE_ACCESS_H

#include <experimental/filesystem>

#include "vector.h"
#include "database.h"

namespace file_access
{
    Database databaseFrom(const std::experimental::filesystem::path& path);
    Database databaseFrom(std::istream& fileStream);

    struct VectorCounts {
        std::size_t vector = 0;
        std::size_t value = 0;
    };
    std::istream& operator>>(std::istream& stream, VectorCounts& vectorCounts);
    std::istream& operator>>(std::istream& stream, Vector& vector);
};

#endif //TT1_CONTEXTGRAPH_FILE_ACCESS_H
