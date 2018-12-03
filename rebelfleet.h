#ifndef STARWARS_REBELFLEET_H
#define STARWARS_REBELFLEET_H

#include <cassert>
#include <type_traits>

template<typename U, bool isAttacker, int minSpeed, int maxSpeed>
class RebelStarship {
public:
    template<typename T = U>
    RebelStarship(std::enable_if_t<isAttacker, T> shield, U speed, U attackPower) : shield(shield), speed(speed),
                                                                                    attackPower(attackPower) {
        checkParameters();
    }

    template<typename T = U>
    RebelStarship(std::enable_if_t<!isAttacker, T> shield, U speed) : shield(shield), speed(speed),
                                                                                    attackPower(static_cast<U>(0)) {
        checkParameters();
    }

    U getShield() const {
        return this->shield;
    }

    U getSpeed() const {
        return this->speed;
    }

    void takeDamage(U damage) {
        if (damage > this->getShield()) {
            this->shield = static_cast<U>(0);
        } else {
            this->shield -= damage;
        }
    }

    template<typename T = U, bool b = isAttacker, int mins = minSpeed, int maxs = maxSpeed>
    std::enable_if_t<isAttacker, T> getAttackPower() const {
        return this->attackPower;
    }

    typedef U valueType;

private:
    U shield;
    U speed;
    U attackPower;

    void checkParameters() const {
        checkSpeed();
        checkShield();
        checkAttackPower();
    }

    void checkSpeed() const {
        assert(minSpeed <= this->speed && this->speed <= maxSpeed);
    }

    void checkShield() const {
        assert(this->shield >= static_cast<U>(0));
    }

    void checkAttackPower() const {
        assert(this->attackPower >= static_cast<U>(0));
    }
};

template<typename U>
using StarCruiser = RebelStarship<U, true, 99999, 299795>;

template<typename U>
using XWing = RebelStarship<U, true, 299796, 2997960>;

template<typename U>
using Explorer = RebelStarship<U, false, 299796, 2997960>;


#endif //STARWARS_REBELFLEET_H
