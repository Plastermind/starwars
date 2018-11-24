//
// Created by skonrad on 24/11/18.
//

#define BOOST_TEST_MODULE StarwarsTests

#include <boost/test/included/unit_test.hpp>
#include <boost/test/execution_monitor.hpp>
#include "rebelfleet.h"
#include "imperialfleet.h"
//#include "battle.h"
#include <cassert>


struct StarCruiserInfo {
    static constexpr int minSpeed = 99999;
    static constexpr int maxSpeed = 299795;
};

struct ExplorerInfo {
    static constexpr int minSpeed = 299796;
    static constexpr int maxSpeed = 2997960;
};

struct XWingInfo : public ExplorerInfo {
};


template<typename U, typename S>
bool testRebelConstruction(U shield, U speed) {
    S ship(shield, speed);

    return ship.getShield() == shield
           && ship.getSpeed() == speed;

}

template<typename U, typename S>
bool testRebelConstruction(U shield, U speed, U attackPower) {
    S ship(shield, speed, attackPower);

    return ship.getShield() == shield
           && ship.getSpeed() == speed
           && ship.getAttackPower() == attackPower;

}


template<typename U, typename T>
bool checkDamageTake(T &ship, U dmg, U result) {
    ship.takeDamage(dmg);
    return ship.getShield() == result;
}

template<typename U, typename T>
bool checkDamageTake(T &&ship, U dmg, U result) {
    ship.takeDamage(dmg);
    return ship.getShield() == result;
}

/*

BOOST_AUTO_TEST_SUITE(ProvidedTests);

    BOOST_AUTO_TEST_CASE(example) {

        XWing<float> xwing(100.0f, 300000.0f, 50.0f);
        Explorer<int> explorer(150, 400000);
        StarCruiser<unsigned> cruiser(1234, 100000, 11);
        DeathStar<long> deathStar(10000, 75);
        TIEFighter<unsigned> fighter(50, 9);
        ImperialDestroyer<int> destroyer(150, 20);
        auto battle = SpaceBattle < short,
        1, 23,
                DeathStar < long >,
                Explorer<int>,
                TIEFighter < unsigned >,
                XWing < float >> (deathStar,
                        explorer,
                        fighter,
                        xwing);

        BOOST_CHECK_EQUAL(battle.countRebelFleet(), 2);
        BOOST_CHECK_EQUAL(battle.countImperialFleet(), 2);

        battle.tick(2);
        BOOST_CHECK_EQUAL(battle.countRebelFleet(), 2);
        BOOST_CHECK_EQUAL(battle.countImperialFleet(), 1);

        battle.tick(1);
        BOOST_CHECK_EQUAL(battle.countRebelFleet(), 2);
        BOOST_CHECK_EQUAL(battle.countImperialFleet(), 1);

        battle.tick(4);
        BOOST_CHECK_EQUAL(battle.countRebelFleet(), 0);
        BOOST_CHECK_EQUAL(battle.countImperialFleet(), 1);

        battle.tick(1); // Wypisuje "IMPERIUM WON\n".
    }

BOOST_AUTO_TEST_SUITE_END();

 */

BOOST_AUTO_TEST_SUITE(Rebels);

    BOOST_AUTO_TEST_CASE(attackers) {


        BOOST_CHECK((testRebelConstruction<unsigned, StarCruiser<unsigned> >(100, StarCruiserInfo::minSpeed, 12)));
        BOOST_CHECK((testRebelConstruction<unsigned, StarCruiser<unsigned> >(100, StarCruiserInfo::maxSpeed, 12)));


        BOOST_CHECK((checkDamageTake<unsigned>(StarCruiser<unsigned>(0, StarCruiserInfo::minSpeed, 12), 100, 0)));
        BOOST_CHECK((checkDamageTake<unsigned>(StarCruiser<unsigned>(1, StarCruiserInfo::minSpeed, 12), 100, 0)));
        BOOST_CHECK((checkDamageTake<unsigned>(StarCruiser<unsigned>(100, StarCruiserInfo::minSpeed, 12), 100, 0)));

        {
            StarCruiser<unsigned> ship(100, StarCruiserInfo::minSpeed, 42);
            BOOST_CHECK((checkDamageTake<unsigned>(ship, 8, 92)));
            BOOST_CHECK((checkDamageTake<unsigned>(ship, 42, 50)));
            BOOST_CHECK((checkDamageTake<unsigned>(ship, 999999, 0)));

        }


    }

    BOOST_AUTO_TEST_CASE(nonAttackers) {
        BOOST_CHECK((testRebelConstruction<float, Explorer<float> >(77, ExplorerInfo::minSpeed)));
        BOOST_CHECK((testRebelConstruction<float, Explorer<float> >(24, ExplorerInfo::maxSpeed)));

        {
            Explorer<float> ship(12.34, ExplorerInfo::minSpeed);
            BOOST_CHECK((checkDamageTake<float>(ship, 0.12, 12.22)));
            BOOST_CHECK((checkDamageTake<float>(ship, 1.10, 11.12)));
            BOOST_CHECK((checkDamageTake<float>(ship, 999999.999999, 0.0)));
        }


    }

BOOST_AUTO_TEST_SUITE_END();


BOOST_AUTO_TEST_SUITE(Empire);

    BOOST_AUTO_TEST_CASE(all) {

    }

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(Battle);


BOOST_AUTO_TEST_SUITE_END();