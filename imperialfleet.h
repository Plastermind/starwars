//
// Created by skonrad on 24/11/18.
//

#ifndef STARWARS_IMPERIALFLEET_H
#define STARWARS_IMPERIALFLEET_H

#include "rebelfleet.h"
//todo co jak tarcze ujemne
//todo co jak attack power ujemne

template <typename U>
class ImperialStarship {
public:
    ImperialStarship(U shield, U attackPower) : shield(shield), attackPower(attackPower) {}

    U getShield() const {
        return this->shield;
    }

    U getAttackPower() const {
        return this->attackPower;
    }

    //todo co jak damage ujemne
    void takeDamage(U damage) {
        if (damage > this->getShield()) {
            this->shield = static_cast<U>(0);
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


#endif //STARWARS_IMPERIALFLEET_H
