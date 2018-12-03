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


template<typename I, typename R>
void attack(I &imperialShip, R &rebelShip) {
    attack(imperialShip, rebelShip);
}

template<typename I, typename U, int minSpeed, int maxSpeed>
void attack(I& imperialShip, RebelStarship<U, false, minSpeed, maxSpeed>& rebelShip) {
    bool isImperialShipNotDestroyed = imperialShip.getShield() >= 0;
    if (isImperialShipNotDestroyed) {
        rebelShip.takeDamage(imperialShip.getAttackPower());
    }

}

template<typename I, typename U, int minSpeed, int maxSpeed>
void attack(I& imperialShip, RebelStarship<U, true, minSpeed, maxSpeed>& rebelShip) {

    bool isImperialShipNotDestroyed = imperialShip.getShield() >= 0;
    if (isImperialShipNotDestroyed) {
        bool isRebelNotDestroyed = rebelShip.getShield() >= 0;

        rebelShip.takeDamage(imperialShip.getAttackPower());

        if (isRebelNotDestroyed) {
            imperialShip.takeDamage(rebelShip.getAttackPower());
        }
    }
}


#endif //STARWARS_IMPERIALFLEET_H
