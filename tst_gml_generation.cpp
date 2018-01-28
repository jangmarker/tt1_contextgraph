#include "3rdparty/catch.hpp"

#include "helper_tst.h"

#include "gml_generation.h"

static const std::string_view onlyRootGml =
R"(graph [
  directed 0
  node [
    id "picard"
    label "picard"
  ]
]
)";

static const std::string_view rootTwoNeighborsGml =
R"(graph [
  directed 0
  node [
    id "data"
    label "data"
  ]
  node [
    id "picard"
    label "picard"
  ]
  node [
    id "riker"
    label "riker"
  ]
  edge [
    source "picard"
    target "data"
  ]
  edge [
    source "picard"
    target "riker"
  ]
]
)";

static const std::string_view twoNeighborsDepth2Gml =
R"(graph [
  directed 0
  node [
    id "data"
    label "data"
  ]
  node [
    id "dax"
    label "dax"
  ]
  node [
    id "kira"
    label "kira"
  ]
  node [
    id "picard"
    label "picard"
  ]
  node [
    id "riker"
    label "riker"
  ]
  node [
    id "saru"
    label "saru"
  ]
  node [
    id "trip"
    label "trip"
  ]
  edge [
    source "data"
    target "dax"
  ]
  edge [
    source "data"
    target "trip"
  ]
  edge [
    source "picard"
    target "data"
  ]
  edge [
    source "picard"
    target "riker"
  ]
  edge [
    source "riker"
    target "kira"
  ]
  edge [
    source "riker"
    target "saru"
  ]
]
)";

TEST_CASE("GML generation")
{
    using namespace gml_generation;

    std::stringstream stream;

    SECTION("only root node") {
        auto res = make_searchresult("picard");
        stream << res;

        REQUIRE(read(stream) == onlyRootGml);
    }

    SECTION("root with two neighbors") {
        auto res = make_searchresult("picard",
                                     make_neighbors(
                                       make_searchresult("riker"),
                                       make_searchresult("data")
                                    ));
        stream << res;

        REQUIRE(read(stream) == rootTwoNeighborsGml);
    }

    SECTION("root with two neighbors, depth 2") {
        auto res = make_searchresult("picard",
                                     make_neighbors(
                                       make_searchresult("riker",
                                         make_neighbors(
                                           make_searchresult("saru"),
                                           make_searchresult("kira")
                                         )
                                       ),
                                       make_searchresult("data",
                                         make_neighbors(
                                           make_searchresult("trip"),
                                           make_searchresult("dax")
                                         )
                                       )
                                     ));
        stream << res;

        REQUIRE(read(stream) == twoNeighborsDepth2Gml);
    }
}