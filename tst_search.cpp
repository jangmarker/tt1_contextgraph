#include "3rdparty/catch.hpp"

#include "vector.h"
#include "database.h"
#include "helper_tst.h"
#include "search.h"

using namespace search;

TEST_CASE("search")
{
    Database db = make_database_3();

    SECTION("depth 0, neighbors 1") {
        auto res = search::search(db, "picard", NeighborCount{0}, Depth{1});
        REQUIRE(res->word == "picard");
        REQUIRE(res->neighbors.empty());
    }

    SECTION("depth 1, neighbors 1") {
        auto res = search::search(db, "picard", NeighborCount{1}, Depth{1});
        REQUIRE(res->word == "picard");
        REQUIRE(res->neighbors.size() == 1);
        REQUIRE(res->neighbors[0]->word == "riker");
        REQUIRE(res->neighbors[0]->neighbors.empty());
    }

    SECTION("depth 1, neighbors 2") {
        auto res = search::search(db, "picard", NeighborCount{2}, Depth{1});
        REQUIRE(res->word == "picard");
        REQUIRE(res->neighbors.size() == 2);
        REQUIRE(res->neighbors[0]->word == "riker");
        REQUIRE(res->neighbors[0]->neighbors.empty());
        REQUIRE(res->neighbors[1]->word == "archer");
        REQUIRE(res->neighbors[1]->neighbors.empty());
    }

    SECTION("depth 2, neighbors 1") {
        auto res = search::search(db, "picard", NeighborCount{1}, Depth{2});
        REQUIRE(res->word == "picard");
        REQUIRE(res->neighbors.size() == 1);
        REQUIRE(res->neighbors[0]->word == "riker");
        REQUIRE(res->neighbors[0]->neighbors.size() == 1);
        REQUIRE(res->neighbors[0]->neighbors[0]->word == "picard");
        REQUIRE(res->neighbors[0]->neighbors[0]->neighbors.empty());
    }
}