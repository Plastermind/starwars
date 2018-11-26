//
// Created by skonrad on 24/11/18.
//

#ifndef ZAD4_IMPERIALFLEET_H
#define ZAD4_IMPERIALFLEET_H

#include "rebelfleet.h"

template <typename U>
class ImperialStarship {
public:
    ImperialStarship(U shield, U attackPower) : shield(shield), attackPower(attackPower) {}

    U getShield() {
        return this->shield;
    }

    U getAttackPower() {
        return this->attackPower;
    }

    void takeDamage(U damage) {
        if (damage > this->getShield()) {
            this->shield = 0;
        } else {
            this->shield -= damage;
        }
    }

    typedef U valueType;

private:
    U shield;
    U attackPower;
};

template<typename U>
using DeathStar = ImperialStarship<U>;

template<typename U>
using ImperialDestroyer = ImperialStarship<U>;

template<typename U>
using TIEFighter = ImperialStarship<U>;


template<typename I, typename T>
void attack(I& imperialShip, T& rebelShip) {
    rebelShip.takeDamage(imperialShip.getAttackPower());
}

template<typename I, typename T>
void attack(I& imperialShip, XWing<T>& xwing) {
    xwing.takeDamage(imperialShip.getAttackPower());
    imperialShip.takeDamage(xwing.getAttackPower());
}

template<typename I, typename T>
void attack(I& imperialShip, StarCruiser<T>& starCruiser) {
    starCruiser.takeDamage(imperialShip.getAttackPower());
    imperialShip.takeDamage(starCruiser.getAttackPower());
}


#endif //ZAD4_IMPERIALFLEET_H
