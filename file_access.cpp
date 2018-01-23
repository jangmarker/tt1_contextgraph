#include <fstream>
#include <cmath>

#include "file_access.h"

Database file_access::databaseFromFile(const std::experimental::filesystem::path& path)
{
    std::ifstream fileStream(path);

    VectorCounts counts;
    fileStream >> counts;

    std::vector<Vector> vectors;
    vectors.reserve(counts.vector);
    for (int l = 0; l < counts.vector; ++l) {
        fileStream >> (vectors.emplace_back(counts.vector));
    }

    Database db;
    db.set_vectors(std::move(vectors));

    return db;
}

std::istream& file_access::operator>>(std::istream& stream, file_access::VectorCounts& vectorCounts)
{
    stream >> vectorCounts.vector;
    stream >> vectorCounts.value;
    return stream;
}

std::istream& file_access::operator>>(std::istream& stream, Vector& vector)
{
    double euclideanNormSquared = 0;

    stream >> vector.word;
    for (int i = 0; i < vector.values.capacity(); ++i) {
        stream >> vector.values[i];
        euclideanNormSquared += vector.values[i] * vector.values[i];
    }
    vector.euclideanNorm = std::sqrt(euclideanNormSquared);

    return stream;
}
