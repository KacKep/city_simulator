#include <catch2/catch_test_macros.hpp>
#include <vector>
#include "Shop.hpp"

TEST_CASE("Building spot validity", "[building]") {
    std::vector<std::vector<int>> map0 = {
        {2, 2, 2, 2, 2},
        {2, 1, 1, 1, 2},
        {2, 1, 0, 1, 2},
        {2, 1, 1, 1, 2},
        {2, 2, 2, 2, 2}
    };
    std::vector<std::vector<int>> map1 = {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 1, 0, 1, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0}
    };

    std::vector<std::vector<int>> map2 = {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 1, 2, 1, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0}
    };

    Shop test_building; 
    //  1x1 building
    test_building.setSize(sf::Vector2f(10, 10));

    SECTION("Valid place") {
        REQUIRE(test_building.Build(map0, 5, 5));
    }

    SECTION("No valid place ") {
        REQUIRE_FALSE(test_building.Build(map1, 5, 5));
    }

    SECTION("Corner placement check") {
        REQUIRE(test_building.Build(map2, 5, 5));
    }
    // 2x2 building
    test_building.setSize(sf::Vector2f(20, 20));

    SECTION("Valid place") {
        REQUIRE(test_building.Build(map0, 5, 5));
        REQUIRE_FALSE(test_building.Build(map0, 5, 5));
    }

    SECTION("No valid corner placement") {
        REQUIRE_FALSE(test_building.Build(map2, 5, 5));
    }

    // 5x5 building too big for the map
    test_building.setSize(sf::Vector2f(50, 50));

    SECTION("not enought space check") {
        REQUIRE_FALSE(test_building.Build(map0, 5, 5));
    }

}
