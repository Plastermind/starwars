//
// Created by skonrad on 24/11/18.
//

#define BOOST_TEST_MODULE StarwarsTests

#include <boost/test/included/unit_test.hpp>
#include <boost/test/execution_monitor.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include "rebelfleet.h"
#include "imperialfleet.h"
#include "battle.h"
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

template<typename U, typename S>
bool testEmpireConstruction(U shield, U attackPower) {
    S ship(shield, attackPower);

    return ship.getShield() == shield
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



BOOST_AUTO_TEST_SUITE(Rebels);

    BOOST_AUTO_TEST_CASE(attackers) {


        BOOST_CHECK((testRebelConstruction<unsigned, StarCruiser<unsigned> >(100, StarCruiserInfo::minSpeed, 12)));
        BOOST_CHECK((testRebelConstruction<unsigned, StarCruiser<unsigned> >(100, StarCruiserInfo::maxSpeed, 12)));
        BOOST_CHECK((testRebelConstruction<boost::multiprecision::cpp_int, StarCruiser<boost::multiprecision::cpp_int> >(100, StarCruiserInfo::maxSpeed, 12)));


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
        BOOST_CHECK((testEmpireConstruction<unsigned, DeathStar<unsigned> >(100, 12)));
        BOOST_CHECK((testEmpireConstruction<double, TIEFighter<double> >(100, 12)));
        BOOST_CHECK((testEmpireConstruction<boost::multiprecision::cpp_int, ImperialDestroyer<boost::multiprecision::cpp_int> >(100, 12)));


        BOOST_CHECK((checkDamageTake<unsigned>(DeathStar<unsigned>(0, 12), 100, 0)));
        BOOST_CHECK((checkDamageTake<unsigned>(DeathStar<unsigned>(1, 12), 100, 0)));
        BOOST_CHECK((checkDamageTake<unsigned>(DeathStar<unsigned>(100, 12), 9, 91)));
        BOOST_CHECK((checkDamageTake<boost::multiprecision::cpp_int>(DeathStar<boost::multiprecision::cpp_int>(100, 12), 9, 91)));


        {
            DeathStar<unsigned> ship(100, 42);
            BOOST_CHECK((checkDamageTake<unsigned>(ship, 8, 92)));
            BOOST_CHECK((checkDamageTake<unsigned>(ship, 42, 50)));
            BOOST_CHECK((checkDamageTake<unsigned>(ship, 999999, 0)));

        }
    }

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(Battle);

    BOOST_AUTO_TEST_CASE(construction) {
        {
            XWing<float> xwing(100.0f, 300000.0f, 50.0f);
            Explorer<int> explorer(150, 400000);
            StarCruiser<unsigned> cruiser(1234, 100000, 11);
            DeathStar<long> deathStar(10000, 75);
            TIEFighter<unsigned> fighter(50, 9);
            //ImperialDestroyer<int> destroyer(150, 20);
            auto battle = SpaceBattle<short,
                    1, 23,
                    DeathStar<long>,
                    Explorer<int>,
                    TIEFighter<unsigned>,
                    XWing<float >>(deathStar,
                                   explorer,
                                   fighter,
                                   xwing);
            {
                std::vector<short> res{0, 1, 4, 9, 16};

                BOOST_REQUIRE_EQUAL(battle.debug_get_attack_moments().size(), res.size());

                for (int i = 0; i < res.size(); ++i) {
                    BOOST_CHECK_EQUAL(battle.debug_get_attack_moments()[i], res[i]);
                }


                BOOST_CHECK_EQUAL(battle.countRebelFleet(), 2);
                BOOST_CHECK_EQUAL(battle.countImperialFleet(), 2);
            }
        }

        {
            XWing<float> xwing(100.0f, 300000.0f, 50.0f);
            XWing<float> xwing2(0.0f, 300000.0f, 50.0f);
            Explorer<int> explorer(150, 400000);
            Explorer<float> explorer2(0.0, 400000.0);
            StarCruiser<unsigned> cruiser(1234, 100000, 11);

            StarCruiser<unsigned> cruiser2(0, 100000, 11);
            StarCruiser<float> cruiser3(1234, 100000, 11);
            DeathStar<long> deathStar(10000, 75);
            TIEFighter<unsigned> fighter(50, 9);
            TIEFighter<unsigned> fighter2(0, 9);
            ImperialDestroyer<int> destroyer(150, 20);
            ImperialDestroyer<boost::multiprecision::cpp_int> destroyer2(0, 20);

            auto battle = SpaceBattle<int,
                    20, 50,
                    StarCruiser<unsigned>,
                    StarCruiser<unsigned>,
                    StarCruiser<float>,
                    ImperialDestroyer<int>,
                    ImperialDestroyer<boost::multiprecision::cpp_int>,
                    DeathStar<long>,
                    Explorer<int>,
                    Explorer<float>,
                    TIEFighter<unsigned>,
                    TIEFighter<unsigned>,
                    XWing<float >,
                    XWing<float >>(
                    cruiser,
                    cruiser2,
                    cruiser3,
                            destroyer,
                                   destroyer2,
                            deathStar,
                                   explorer,
                                   explorer2,
                                   fighter,
                                   fighter2,
                                   xwing,
                                   xwing2
                                   );

            std::vector<int> res{0, 1, 4, 9, 16, 25, 36, 49};

            BOOST_REQUIRE_EQUAL(battle.debug_get_attack_moments().size(), res.size());

            for (int i = 0; i < res.size(); ++i) {
                BOOST_CHECK_EQUAL(battle.debug_get_attack_moments()[i], res[i]);
            }

            BOOST_CHECK_EQUAL(battle.countImperialFleet(), 3);
            BOOST_CHECK_EQUAL(battle.countRebelFleet(), 4);

        }


    }

    BOOST_AUTO_TEST_CASE(pair) {
        {
            XWing<float> xwing(42, XWingInfo::minSpeed, 2);
            DeathStar<float> ds(42, 3);
            attack(ds, xwing);
            BOOST_CHECK_EQUAL(ds.getShield(), 40);
            BOOST_CHECK_EQUAL(xwing.getShield(), 39);
        }

        {
            XWing<float> xwing(42, XWingInfo::minSpeed, 2000);
            DeathStar<float> ds(42, 2000);
            attack(ds, xwing);
            /* todo czy tak ma byc */
            BOOST_CHECK_EQUAL(ds.getShield(), 0);
            BOOST_CHECK_EQUAL(xwing.getShield(), 0);
        }

        {
            XWing<double> xw(100, XWingInfo::minSpeed, 1);
            StarCruiser<double> sc(101, StarCruiserInfo::minSpeed, 2);
            Explorer<double> ex(102, ExplorerInfo::minSpeed);

            DeathStar<float> ds(103, 3);
            ImperialDestroyer<float> id(104, 4);
            TIEFighter<float> tf(105, 5);

            attack(ds, xw);
            attack(ds, sc);
            attack(ds, ex);

            attack(id, xw);
            attack(id, sc);
            attack(id, ex);

            attack(tf, xw);
            attack(tf, sc);
            attack(tf, ex);

            BOOST_CHECK_EQUAL(xw.getShield(), 88);
            BOOST_CHECK_EQUAL(sc.getShield(), 89);
            BOOST_CHECK_EQUAL(ex.getShield(), 90);

            BOOST_CHECK_EQUAL(ds.getShield(), 100);
            BOOST_CHECK_EQUAL(id.getShield(), 101);
            BOOST_CHECK_EQUAL(tf.getShield(), 102);
        }


        {
            Explorer<float> exp(42, ExplorerInfo::minSpeed);
            DeathStar<float> ds(42, 2000);
            attack(ds, exp);
            /* todo czy tak ma byc */
            BOOST_CHECK_EQUAL(ds.getShield(), 42);
            BOOST_CHECK_EQUAL(exp.getShield(), 0);
        }


    }

BOOST_AUTO_TEST_SUITE_END();