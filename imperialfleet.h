#ifndef STARWARS_IMPERIALFLEET_H
#define STARWARS_IMPERIALFLEET_H

#include "rebelfleet.h"

template <typename U>
class ImperialStarship {
public:
    ImperialStarship(U shield, U attackPower) : shield(shield), attackPower(attackPower) {
        checkParameters();
    }

    U getShield() const {
        return this->shield;
    }

    U getAttackPower() const {
        return this->attackPower;
    }

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

    void checkParameters() const {
        checkShield();
        checkAttackPower();
    }

    void checkShield() const {
        assert(this->shield >= static_cast<U>(0));
    }

    void checkAttackPower() const {
        assert(this->attackPower >= static_cast<U>(0));
    }
};

template<typename U>
using DeathStar = ImperialStarship<U>;

template<typename U>
using ImperialDestroyer = ImperialStarship<U>;


template<typename U>
using TIEFighter = ImperialStarship<U>;

template<typename I>
bool isImperial(ImperialStarship<I>) {
    return true;
}

template<typename T>
bool isImperial(T) {
    return false;
}

template<typename R, int minSpeed, int maxSpeed, bool isAttacker>
bool isRebel(RebelStarship<R, isAttacker, minSpeed, maxSpeed>) {
    return true;
}

template<typename T>
bool isRebel(T) {
    return false;
}

template<typename I, typename R>
void checkShipsCorrectness(I imperialShip, R rebelShip) {
    assert(isImperial(imperialShip) && isRebel(rebelShip));
}

template<typename I, typename R>
void attack(I& imperialShip, R& rebelShip) {
    checkShipsCorrectness(imperialShip, rebelShip);
    attack(imperialShip, rebelShip);
}

template<typename I, typename R, int minSpeed, int maxSpeed>
void attack(I& imperialShip, RebelStarship<R, false, minSpeed, maxSpeed>& rebelShip) {
    bool isImperialShipNotDestroyed = imperialShip.getShield() > static_cast<typename I::valueType>(0);
    if (isImperialShipNotDestroyed) {
        rebelShip.takeDamage(imperialShip.getAttackPower());
    }

}

template<typename I, typename R, int minSpeed, int maxSpeed>
void attack(I& imperialShip, RebelStarship<R, true, minSpeed, maxSpeed>& rebelShip) {
    bool isImperialShipNotDestroyed = imperialShip.getShield() > static_cast<typename I::valueType>(0);
    if (isImperialShipNotDestroyed) {
        bool isRebelNotDestroyed = rebelShip.getShield() > static_cast<R>(0);

        rebelShip.takeDamage(imperialShip.getAttackPower());

        if (isRebelNotDestroyed) {
            imperialShip.takeDamage(rebelShip.getAttackPower());
        }
    }
}


#endif //STARWARS_IMPERIALFLEET_H
