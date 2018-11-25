//
// Created by skonrad on 24/11/18.
//

#ifndef ZAD4_REBELFLEET_H
#define ZAD4_REBELFLEET_H

#include <assert.h>

template<typename U, typename ...args>
class RebelStarship {
};


template<typename U>
class RebelStarship<U> {
public:
    RebelStarship(U shield, U speed) : shield(shield), speed(speed) {}

    U getShield() {
        return this->shield;
    }

    U getSpeed() {
        return this->speed;
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
    U speed;
};

/* todo czy chodzi o coś w stylu tego czy można dziedziczyć */
template<typename T> using XXX = RebelStarship<T>;


template<typename U>
class Explorer : public RebelStarship<U> {
public:
    Explorer(U shield, U speed) : RebelStarship<U>(shield, speed) {
        assert(299796 <= speed && speed <= 2997960);    //todo
    }


private:
};

template<typename U>
class XWing : public RebelStarship<U> {
public:
    XWing(U shield, U speed, U attackPower) : RebelStarship<U>(shield, speed), attackPower(attackPower) {
        assert(299796 <= speed && speed <= 2997960);    //todo
    }

    U getAttackPower() {
        return attackPower;
    }

private:
    U attackPower;
};


template<typename U>
class StarCruiser : public RebelStarship<U> {
public:
    StarCruiser(U shield, U speed, U attackPower) : RebelStarship<U>(shield, speed), attackPower(attackPower) {
        assert(99999 <= speed && speed <= 299795);  //todo
    }

    U getAttackPower() {
        return attackPower;
    }

private:
    U attackPower;
};

#endif //ZAD4_REBELFLEET_H
