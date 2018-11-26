//
// Created by skonrad on 24/11/18.
//

#ifndef ZAD4_IMPERIALFLEET_H
#define ZAD4_IMPERIALFLEET_H

#include <iostream>
#include "rebelfleet.h"
template <typename U>
class ImperialStarship {
public:
    ImperialStarship(U shield, U attackPower) : shield(shield), attackPower(attackPower) {}

    U getShield() {
        return this->shield;
    }

    void takeDamage(U damage) {
        if (damage > this->getShield()) {
            this->shield = 0;
        } else {
            this->shield -= damage;
        }
    }

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

/*
template<typename U, typename ...args>
class ImperialStarship {
};

template<typename U>
class ImperialStarship<U> {
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
class DeathStar : public ImperialStarship<U> {
public:
    DeathStar(U shield, U attackPower) : ImperialStarship<U>(shield, attackPower) {}

private:
};

template<typename U>
class ImperialDestroyer : public ImperialStarship<U> {
public:
    ImperialDestroyer(U shield, U attackPower) : ImperialStarship<U>(shield, attackPower) {}

private:
};

template<typename U>
class TIEFighter : public ImperialStarship<U> {
public:
    TIEFighter(U shield, U attackPower) : RebelStarship<U>(shield, attackPower) {}

private:
};


// funkcja attack powinna zachowywać się inaczej dla drugiego argumentu będącego xwingiem albo starcruiserem
// stawiam, że trzeba użyć specjalizacji, ale niestety nie wiem jak to zrobić dla "zbioru typów", a nie konkretnego typu

template<typename I, typename R>
void attack(I& imperialShip, R& rebelShip) {
    std::cout << "normal attack" << std::endl;
    rebelShip.takeDamage(imperialShip.getAttackPower());
}

template <>
void attack<DeathStar<int>, XWing<int>> (DeathStar<int>& imperialShip, XWing<int>& xwing) {
    std::cout << "special attack" << std::endl;
    xwing.takeDamage(imperialShip.getAttackPower());
    imperialShip.takeDamage(xwing.getAttackPower());
}

*/

template<typename I, typename R>
void attack(I& imperialShip, R& rebelShip) {
    std::cout << "normal attack" << std::endl;
    rebelShip.takeDamage(imperialShip.getAttackPower());
}

template<typename I, typename R>
void attack(I& imperialShip, XWing<R> &xwing) {
    xwing.takeDamage(imperialShip.getAttackPower());
    imperialShip.takeDamage(xwing.getAttackPower());
}



/*
template <>
void attack<DeathStar<int>, XWing<int>> (DeathStar<int>& imperialShip, XWing<int>& xwing) {
    std::cout << "special attack" << std::endl;
    xwing.takeDamage(imperialShip.getAttackPower());
    imperialShip.takeDamage(xwing.getAttackPower());
}*/

#endif //ZAD4_IMPERIALFLEET_H
