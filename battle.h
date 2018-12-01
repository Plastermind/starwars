//
// Created by piotr on 25.11.18.
//

#ifndef STARWARS_BATTLE_H
#define STARWARS_BATTLE_H

#include <cstddef>
#include <iostream>
#include <vector>
#include <tuple>
#include "rebelfleet.h"
#include "imperialfleet.h"

template<typename T, T t0, T t1, typename ...Args>
class SpaceBattle {
public:
    SpaceBattle(Args ...args) : ships(args...) {
        actualTime = t0;
        maxTime = t1;

        initialFleetCount();
    }

    size_t countImperialFleet() const {
        return empireCount;
    }

    size_t countRebelFleet() const {
        return rebelCount;
    }

    void tick(T timeStep) {
        if (countImperialFleet() == 0 || countRebelFleet() == 0) {
            if (countImperialFleet() == 0 && countRebelFleet() == 0) {
                std::cout << "DRAW" << std::endl;
            } else if (countImperialFleet() == 0) {
                std::cout << "REBELLION WON" << std::endl;
            } else {
                std::cout << "IMPERIUM WON" << std::endl;
            }
        } else {
            if (isAttackTime(actualTime)) {
                fight();
            }

            actualTime = (actualTime + timeStep) % (maxTime + static_cast<T>(1));
        }
    }

    // todo delete
    void debug_print() {
        std::cout << actualTime << " " << maxTime << std::endl;
    }

    // todo delete
    void debug_print_attack_moments() {
        for (auto m : attackMoments) {
            std::cerr << m << " ";
        }
        std::cerr << std::endl;
    }

    // todo delete
    T debug_get_current_time() {
        return actualTime;
    }

    // todo delete
    std::vector<T> debug_get_attack_moments() {
        std::vector<T> res;
        for (auto i : attackMoments) {
            res.emplace_back(i);
        }
        return res;
    }

private:
    static_assert(t0 <= t1);
    static_assert(static_cast<T>(0) <= t0);

    T actualTime;
    T maxTime;
    size_t empireCount = 0;
    size_t rebelCount = 0;

    std::tuple<Args...> ships;

    bool isAttackTime(T t) const {
        size_t b = 0;
        size_t e = attackMoments.size();
        size_t m = (e - b) / 2 + b;

        while (b < e) {
            if (attackMoments[m] < t) {
                b = m + 1;
            } else if (attackMoments[m] > t) {
                e = m;
            } else {
                return true;
            }
            m = (e - b) / 2 + b;
        }

        return false;
    }

    void fight() {
        if constexpr(sizeof...(Args) != 0) {
            iterateEmpire<0>(std::get<0>(ships));
        }

    }

    template<typename ShipT>
    static bool shipDestroyed(const ShipT &ship) {
        return ship.getShield() <= static_cast<typename ShipT::valueType>(0);
    }


    template<size_t i, typename ImperialShipT, typename U, bool isAttacker, int minSpeed, int maxSpeed>
    void iterateRebels(ImperialShipT &imperialShip, RebelStarship<U, isAttacker, minSpeed, maxSpeed> &rebelShip) {
        //std::cerr << i << "Rebel" << std::endl;

        if (!shipDestroyed(rebelShip)) {
            attack(imperialShip, rebelShip);

            if (shipDestroyed(rebelShip)) {
                --rebelCount;
            }
        }

        if (!shipDestroyed(imperialShip)) {
            if constexpr (i + 1 < sizeof...(Args)) {
                iterateRebels<i + 1>(imperialShip, std::get<i + 1>(ships));
            }
        } else {
            --empireCount;
        }


    }

    template<size_t i, typename ImperialShipT, typename ShipT>
    void iterateRebels(ImperialShipT &imperialShip, const ShipT &ship) {
        //std::cerr << i << "not Rebel" << std::endl;
        (void) ship; //suppress warning

        if constexpr (i + 1 < sizeof...(Args)) {
            iterateRebels<i + 1>(imperialShip, std::get<i + 1>(ships));
        }

    }


    template<size_t i, typename U>
    void iterateEmpire(ImperialStarship<U> &imperialShip) {
        //std::cerr << i << "Empire" << std::endl;

        if (!shipDestroyed(imperialShip)) {
            iterateRebels<0>(imperialShip, std::get<0>(ships));

        }
        if constexpr (i + 1 < sizeof...(Args)) {
            iterateEmpire<i + 1>(std::get<i + 1>(ships));
        }

    }

    template<size_t i, typename ShipT>
    void iterateEmpire(const ShipT &ship) {
        //std::cerr << i << "not Empire" << std::endl;
        (void) ship; //suppress warning

        if constexpr (i + 1 < sizeof...(Args)) {
            iterateEmpire<i + 1>(std::get<i + 1>(ships));
        }

    }

    void initialFleetCount() {
        if constexpr(sizeof...(Args) != 0) {
            initialFleetCount < 0 > (std::get<0>(ships));
        }
    }

    template<size_t i, typename U>
    void initialFleetCount(const ImperialStarship<U> &imperialShip) {
        if (!shipDestroyed(imperialShip)) {
            ++empireCount;
        }

        if constexpr (i + 1 < sizeof...(Args)) {
            initialFleetCount<i + 1>(std::get<i + 1>(ships));
        }
    }

    template<size_t i, typename U, bool isAttacker, int minSpeed, int maxSpeed>
    void initialFleetCount(const RebelStarship<U, isAttacker, minSpeed, maxSpeed> &rebelShip) {
        if (!shipDestroyed(rebelShip)) {
            ++rebelCount;
        }

        if constexpr (i + 1 < sizeof...(Args)) {
            initialFleetCount<i + 1>(std::get<i + 1>(ships));
        }
    }

    static constexpr size_t howManySquares() {
        size_t result = 0;
        //bool overflow = false;
        for (T i = static_cast<T>(0); /*!overflow &&*/ i * i <= t1; i += static_cast<T>(1)) { //todo change?
            ++result;
            /*if ((i + 1) * (i + 1) < i * i) {
                overflow = true;
            }*/
        }

        return result;
    }

    template<size_t numOfSquares, T ...squares>
    static constexpr std::array<T, numOfSquares + (sizeof...(squares))> calcSquares() {
        constexpr T offset = static_cast<T>(sizeof...(squares));
        constexpr T nextSquare = static_cast<T>(offset * offset);
        if constexpr (numOfSquares == 0) {
            constexpr size_t size = (sizeof...(squares));
            return std::array<T, size>{{squares...}};
        } else {
            return calcSquares<numOfSquares - 1, squares..., nextSquare>();
        }

    }


    /*
    //todo czy to jest compile time
    template<size_t numOfSquares>
    static constexpr std::array<T, numOfSquares> calcSquares() {
        std::array<T, numOfSquares> result;
        for (size_t i = 0; i < numOfSquares; ++i) {
            T offset = static_cast<T>(i);
            T nextSquare = (offset) * (offset);
            result[i] = nextSquare;
        }

        return result;
    }*/

    const std::array<T, howManySquares()> attackMoments = calcSquares<howManySquares()>();


};


#endif //STARWARS_BATTLE_H
//-D CMAKE_CXX_COMPILER=clang++