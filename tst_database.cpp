#include <cmath>

#include "3rdparty/catch.hpp"

#include "vector.h"
#include "database.h"

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

TEST_CASE("most similar")
{
    Vector vec1 = make_vector("picard", {0.1, 0.2});
    Vector vec2 = make_vector("riker", {0.3, 0.4});
    Vector vec3 = make_vector("archer", {8, 9});

    std::vector<Vector> vectors = {vec1, vec2, vec3};

    Database db;
    db.set_vectors(std::move(vectors));

    SECTION("query one") {
        auto similar = db.most_similar("picard", 1);

        REQUIRE(similar.size() == 1);
        REQUIRE(similar[0] == "riker");
    }

    SECTION("query multiple") {
        auto similar = db.most_similar("picard", 2);
        REQUIRE(similar.size() == 2);
        REQUIRE(similar == std::vector<std::string>{"riker", "archer"});
    }

    SECTION("query more than available") {
        auto similar = db.most_similar("picard", 5);
        REQUIRE(similar.size() == 2);
    }
}