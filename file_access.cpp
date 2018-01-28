#include <fstream>
#include <cmath>

#include "file_access.h"

Database file_access::databaseFrom(const std::experimental::filesystem::path& path)
{
    std::ifstream fileStream(path);
    return databaseFrom(fileStream);
}

Database file_access::databaseFrom(std::istream& fileStream)
{
    VectorCounts counts;
    fileStream >> counts;

    std::vector<Vector> vectors;
    vectors.reserve(counts.vector);
    for (int l = 0; l < counts.vector; ++l) {
        fileStream >> (vectors.emplace_back(counts.value));
    }

    Database db;
    db.set_vectors(move(vectors));
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
    for (double& value : vector.values) {
        stream >> value;
        euclideanNormSquared += value * value;
    }
    vector.euclideanNorm = std::sqrt(euclideanNormSquared);

    return stream;
}
