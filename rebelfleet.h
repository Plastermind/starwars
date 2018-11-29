//
// Created by skonrad on 24/11/18.
//

#ifndef ZAD4_REBELFLEET_H
#define ZAD4_REBELFLEET_H

#include <cassert>
#include <type_traits>


//sfinae
//enable_t
//do space batle krotka bo nie moge typow w runtime rozpoznac

template<typename U, bool isAttacker, int minSpeed, int maxSpeed>
class RebelStarship {
public:
    template < typename T = U, bool b = isAttacker, int mins = minSpeed, int maxs = maxSpeed>
    RebelStarship(std::enable_if_t<isAttacker, T> shield, U speed, U attackPower) : shield(shield), speed(speed), attackPower(attackPower) {
        checkSpeed();
    }

    template < typename T = U, bool b = isAttacker, int mins = minSpeed, int maxs = maxSpeed >
    RebelStarship(std::enable_if_t<!isAttacker, T> shield, U speed) : shield(shield), speed(speed) {
        checkSpeed();
    }

    U getShield() const {
        return this->shield;
    }

    U getSpeed() const {
        return this->speed;
    }

    void takeDamage(U damage) {
        if (damage > this->getShield()) {
            this->shield = 0;
        } else {
            this->shield -= damage;
        }
    }

    template < typename T = U, bool b = isAttacker, int mins = minSpeed, int maxs = maxSpeed>
    std::enable_if_t<isAttacker, T> getAttackPower() {
        return this->attackPower;
    }

    typedef U valueType;

private:
    U shield;
    U speed;
    U attackPower;

    void checkSpeed() {
        assert(minSpeed <= speed && speed <= maxSpeed);
    }
};


template<typename U>
using StarCruiser = RebelStarship<U, true, 99999, 299795>;

template<typename U>
using XWing = RebelStarship<U, true, 299796, 2997960>;

template<typename U>
using Explorer = RebelStarship<U, false, 299796, 2997960>;





#endif //ZAD4_REBELFLEET_H
