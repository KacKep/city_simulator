#include <catch2/catch_test_macros.hpp>
#include <vector>
#include "EnumList.hpp"
#include "Human.hpp"

TEST_CASE("Targeting", "[Entity_targeting]") {
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
        {4, 5, 5, 2, 6, 6, 6, 0, 0, 0},
        {4, 5, 5, 2, 6, 6, 6, 0, 0, 0},
        {0, 1, 2, 2, 7, 7, 0, 0, 0, 0},
        {0, 1, 1, 2, 7, 7, 0, 0, 0, 0},
        {0, 0, 0, 2, 0, 0, 0, 0, 0, 0},
        {4, 5, 5, 2, 6, 6, 6, 0, 0, 0},
        {4, 5, 5, 2, 6, 6, 6, 0, 0, 0},
        {0, 1, 2, 2, 7, 7, 0, 0, 0, 0},
        {0, 1, 1, 2, 7, 7, 0, 0, 0, 0},
        {0, 1, 1, 2, 7, 7, 0, 0, 0, 0}
    };
    Human test_subject;
    test_subject.setMap(map0, sf::Vector2i(5, 5));
    // --------------no buildings--------------
    SECTION("Chosen place. Only pavement. Human full and bored") {
        test_subject.walk();
        REQUIRE(test_subject.getTargetTile() == PavementTile);
    }


    SECTION("Chosen place. Only pavement. Guy is poor") {
        test_subject.addMoney(-test_subject.getMoney());
        test_subject.walk();
        REQUIRE(test_subject.getTargetTile() == PavementTile);
    }

    SECTION("Chosen place. Only pavement. Guy is hungry and poor") {
        test_subject.addMoney(-test_subject.getMoney());
        test_subject.addHunger(-test_subject.getHunger());
        test_subject.walk();
        REQUIRE(test_subject.getTargetTile() == PavementTile);
    }

    SECTION("Chosen place. Only pavement. Guy is hungry") {
        test_subject.addHunger(-test_subject.getHunger());
        test_subject.walk();
        REQUIRE(test_subject.getTargetTile() == PavementTile);
    }

    SECTION("Chosen place. Only pavement. Guy is unhealthy, hungry and poor") {
        test_subject.addMoney(-test_subject.getMoney());
        test_subject.addHunger(-test_subject.getHunger());
        test_subject.addHealth(10 - test_subject.getHealth());

        test_subject.walk();
        REQUIRE(test_subject.getTargetTile() == PavementTile);
    }

    SECTION("Chosen place. Only pavement. Guy is unhealthy, hungry and doesn't have enought money for hospital") {
        test_subject.addHunger(-test_subject.getHunger());
        test_subject.addHealth(10 - test_subject.getHealth());

        test_subject.walk();
        REQUIRE(test_subject.getTargetTile() == PavementTile);
    }

    SECTION("Chosen place. Only pavement. Guy is unhealthy and hungry") {
        test_subject.addMoney(600);
        test_subject.addHunger(-test_subject.getHunger());
        test_subject.addHealth(10 - test_subject.getHealth());

        test_subject.walk();
        REQUIRE(test_subject.getTargetTile() == PavementTile);
    }


    //-------------random plane (city with 9 or less lenght or width)--------------
    test_subject.setMap(map1, sf::Vector2i(5, 5));
    SECTION("Chosen place. Only flowers and grass") {
        test_subject.walk();
        REQUIRE(test_subject.getTargetTile() < PavementTile);
    }

    //----------------normal city (not buildings lol)------------
    test_subject.setMap(map2, sf::Vector2i(10, 10));
    SECTION("Chosen place.City with everything") {
        REQUIRE(test_subject.getTargetTile() == PavementTile);
    }

   
    SECTION("Chosen place.City with everything. Guy is poor") {
        test_subject.addMoney(-test_subject.getMoney());
        test_subject.walk();
        REQUIRE(test_subject.getTargetTile() == OfficeBuildingTile);
    }

    SECTION("Chosen place.City with everything. Guy is hungry and poor") {
        test_subject.addMoney(-test_subject.getMoney());
        test_subject.addHunger(-test_subject.getHunger());
        test_subject.walk();
        REQUIRE(test_subject.getTargetTile() == OfficeBuildingTile);
    }

    SECTION("Chosen place.City with everything. Guy is hungry") {
        test_subject.addHunger(-test_subject.getHunger());
        test_subject.walk();
        REQUIRE(test_subject.getTargetTile() == ShopTile);
    }

    SECTION("Chosen place.City with everything. Guy is unhealthy, hungry and poor") {
        test_subject.addMoney(-test_subject.getMoney());
        test_subject.addHunger(-test_subject.getHunger());
        test_subject.addHealth(10-test_subject.getHealth());

        test_subject.walk();
        REQUIRE(test_subject.getTargetTile() == OfficeBuildingTile);
    }

    SECTION("Chosen place.City with everything. Guy is unhealthy, hungry and doesn't have enought money for hospital") {
        test_subject.addHunger(-test_subject.getHunger());
        test_subject.addHealth(10 - test_subject.getHealth());

        test_subject.walk();
        REQUIRE(test_subject.getTargetTile() == ShopTile);
    }

    SECTION("Chosen place.City with everything. Guy is unhealthy and hungry") {
        test_subject.addMoney(600);
        test_subject.addHunger(-test_subject.getHunger());
        test_subject.addHealth(10 - test_subject.getHealth());
        
        test_subject.walk();
        REQUIRE(test_subject.getTargetTile() == HospitalTile);
    }

    SECTION("Chosen place.City with everything. Guy is dead") {
        test_subject.addHealth( - test_subject.getHealth());
        test_subject.walk();
        REQUIRE(test_subject.isDead());
    }
    //Liqour Shop is random so who cares
}