#include <cmath>

#include "3rdparty/catch.hpp"

#include "vector.h"
#include "database.h"
#include "helper_tst.h"

TEST_CASE("most similar")
{
    Database db = make_database_3();

    SECTION("query one") {
        auto similar = db.most_similar("picard", 1);

        REQUIRE(similar.size() == 1);
        REQUIRE(similar[0] == "riker");
    }

    SECTION("query multiple") {
        auto similar = db.most_similar("picard", 2);
        REQUIRE(similar.size() == 2);
        REQUIRE(similar == std::vector<WordView>{"riker", "archer"});
    }

    SECTION("query more than available") {
        auto similar = db.most_similar("picard", 5);
        REQUIRE(similar.size() == 2);
    }

    SECTION("query non-existent") {
        auto similar = db.most_similar("this does not exist", 100);
        REQUIRE(similar.empty());
    }
}