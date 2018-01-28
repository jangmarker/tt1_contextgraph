#include "3rdparty/catch.hpp"

#include "file_access.h"

#include <cmath>
#include <fstream>
#include <experimental/filesystem>

using namespace file_access;

TEST_CASE("read database header")
{
    std::istringstream stream("42 47");

    VectorCounts counts;
    stream >> counts;

    REQUIRE(counts.vector == 42);
    REQUIRE(counts.value == 47);
}

TEST_CASE("read short vector")
{
    std::istringstream stream("der -0.404572 0.754874");

    Vector vector{2};
    stream >> vector;
    std::vector<double> expected{-0.404572, 0.754874};
    double euclideanNorm = std::sqrt(expected[0]*expected[0] + expected[1]*expected[1]);

    REQUIRE(vector.word == "der");
    REQUIRE(vector.values == expected);
    REQUIRE(vector.euclideanNorm == euclideanNorm);
}

TEST_CASE("read short database")
{
    std::istringstream stream(
R"(
4 3
der 0.1 0.2 0.3
die 0.4 0.5 0.6
das 0.7 0.8 0.9
wer 0.0 0.1 -0.2
)");

    Database db = databaseFrom(stream);

    REQUIRE(db.vectors().size() == 4);
    REQUIRE(db.vectors()[0].word == "der");
    REQUIRE(db.vectors()[0].values == std::vector<double>{0.1, 0.2, 0.3});
    REQUIRE(db.vectors()[3].word == "wer");
    REQUIRE(db.vectors()[3].values == std::vector<double>{0.0, 0.1, -0.2});
}

TEST_CASE("read database from file")
{
    namespace fs = std::experimental::filesystem;
    fs::path self(__FILE__);
    fs::path directory = self.parent_path();

    auto db = file_access::databaseFrom(directory / "embeddings" / "test.txt");

    REQUIRE(db.vectors().size() == 3);
    REQUIRE(db.vectors()[0].word == "picard");
    REQUIRE(db.vectors()[0].values == std::vector<double>{0.1, 0.2});
}