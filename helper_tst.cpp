#include "helper_tst.h"

#include <cmath>
#include <sstream>
#include <iterator>

Vector make_vector(std::string_view word, std::initializer_list<double> values)
{
    Vector vec{values.size()};
    vec.word = word;
    vec.values = values;

    double euclideanNormSquared = 0.0;
    for (double value : values) {
        euclideanNormSquared += value * value;
    }
    vec.euclideanNorm = std::sqrt(euclideanNormSquared);

    return vec;
}

Database make_database_3()
{
    Vector vec1 = make_vector("picard", {0.1, 0.2});
    Vector vec2 = make_vector("riker", {0.3, 0.4});
    Vector vec3 = make_vector("archer", {8, 9});

    Database db;
    db.set_vectors(std::vector<Vector>{vec1, vec2, vec3});

    return db;
}

void append_neighbor(search::Neighbors* neighbors)
{ }

search::SearchResultPtr make_searchresult(std::string_view name, search::Neighbors&& neighbors)
{
    return std::make_unique<search::SearchResult>(name, std::move(neighbors));
}

std::string read(std::stringstream& stream)
{
    return std::string{std::istreambuf_iterator<char>(stream), {}};
}
