#ifndef STARWARS_BATTLE_H
#define STARWARS_BATTLE_H

#include <cstddef>
#include <iostream>
#include <tuple>
#include "rebelfleet.h"
#include "imperialfleet.h"

template<typename T, T t0, T t1, typename ...S>
class SpaceBattle {
public:
    SpaceBattle(S ...s) : ships(s...) {
        this->actualTime = t0;
        this->maxTime = t1;

        initialFleetCount();
    }

    size_t countImperialFleet() const {
        return this->empireCount;
    }

    size_t countRebelFleet() const {
        return this->rebelCount;
    }

    void tick(T timeStep) {
        if (countImperialFleet() == 0 && countRebelFleet() == 0) {
            std::cout << "DRAW" << std::endl;
        } else if (countImperialFleet() == 0) {
            std::cout << "REBELLION WON" << std::endl;
        } else if (countRebelFleet() == 0) {
            std::cout << "IMPERIUM WON" << std::endl;
        } else if (isAttackTime(this->actualTime)) {
            fight();
        }

        this->actualTime = (this->actualTime + timeStep) % (this->maxTime + static_cast<T>(1));
    }

private:
    static_assert(t0 <= t1);
    static_assert(static_cast<T>(0) <= t0);

    T actualTime;
    T maxTime;
    size_t empireCount = 0;
    size_t rebelCount = 0;

    std::tuple<S...> ships;

    bool isAttackTime(T t) const {
        auto attackMoment = std::lower_bound(attackMoments.begin(), attackMoments.end(), t);

        if (attackMoment == attackMoments.end())
            return false;
        else
            return t == *attackMoment;
    }

    void fight() {
        if constexpr(sizeof...(S) != 0) {
            iterateEmpire<0>(std::get<0>(this->ships));
        }

    }

    template<typename ShipT>
    static bool shipDestroyed(const ShipT &ship) {
        return ship.getShield() <= static_cast<typename ShipT::valueType>(0);
    }


    template<size_t i, typename ImperialShipT, typename U, bool isAttacker, int minSpeed, int maxSpeed>
    void iterateRebels(ImperialShipT &imperialShip, RebelStarship<U, isAttacker, minSpeed, maxSpeed> &rebelShip) {
        if (!shipDestroyed(rebelShip)) {
            attack(imperialShip, rebelShip);

            if (shipDestroyed(rebelShip)) {
                --(this->rebelCount);
            }
        }

        if (!shipDestroyed(imperialShip)) {
            if constexpr (i + 1 < sizeof...(S)) {
                iterateRebels<i + 1>(imperialShip, std::get<i + 1>(this->ships));
            }
        } else {
            --(this->empireCount);
        }


    }

    template<size_t i, typename ImperialShipT, typename ShipT>
    void iterateRebels(ImperialShipT &imperialShip, const ShipT &) {
        if constexpr (i + 1 < sizeof...(S)) {
            iterateRebels<i + 1>(imperialShip, std::get<i + 1>(this->ships));
        }

    }


    template<size_t i, typename U>
    void iterateEmpire(ImperialStarship<U> &imperialShip) {
        if (!shipDestroyed(imperialShip)) {
            iterateRebels<0>(imperialShip, std::get<0>(this->ships));
        }
        if constexpr (i + 1 < sizeof...(S)) {
            iterateEmpire<i + 1>(std::get<i + 1>(this->ships));
        }

    }

    template<size_t i, typename ShipT>
    void iterateEmpire(const ShipT &) {
        if constexpr (i + 1 < sizeof...(S)) {
            iterateEmpire<i + 1>(std::get<i + 1>(this->ships));
        }
    }

    void initialFleetCount() {
        if constexpr(sizeof...(S) != 0) {
            initialFleetCount < 0 > (std::get<0>(this->ships));
        }
    }

    template<size_t i, typename U>
    void initialFleetCount(const ImperialStarship<U> &imperialShip) {
        if (!shipDestroyed(imperialShip)) {
            ++(this->empireCount);
        }

        if constexpr (i + 1 < sizeof...(S)) {
            initialFleetCount<i + 1>(std::get<i + 1>(this->ships));
        }
    }

    template<size_t i, typename U, bool isAttacker, int minSpeed, int maxSpeed>
    void initialFleetCount(const RebelStarship<U, isAttacker, minSpeed, maxSpeed> &rebelShip) {
        if (!shipDestroyed(rebelShip)) {
            ++(this->rebelCount);
        }

        if constexpr (i + 1 < sizeof...(S)) {
            initialFleetCount<i + 1>(std::get<i + 1>(this->ships));
        }
    }

    static constexpr size_t howManySquares() {
        size_t result = 0;
        for (T i = static_cast<T>(0); i * i <= t1; i += static_cast<T>(1)) {
            ++result;
        }

        return result;
    }

    template<size_t numOfSquares>
    static constexpr std::array<T, numOfSquares> calcSquares() {
        std::array<T, numOfSquares> result = {};
        for (T i = static_cast<T>(0); i * i <= t1; ++i) {
            result[static_cast<size_t>(i)] = i * i;
        }
        return result;
    }

    static constexpr std::array<T, howManySquares()> attackMoments = calcSquares<howManySquares()>();


};

#endif //STARWARS_BATTLE_H
