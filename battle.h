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
        //todo czy czas moze byc double

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

            actualTime = (actualTime + timeStep) % (maxTime + 1);

            //debug_print();
        }
    }

    // helping function, remember to delete
    void debug_print() {
        std::cout << actualTime << " " << maxTime << std::endl;
    }

    void debug_print_attack_moments() {
        for (auto m : attackMoments) {
            std::cerr << m << " ";
        }
        std::cerr << std::endl;
    }

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
        size_t m = (b + e) / 2;

        while (b < e) {
            if (attackMoments[m] < t) {
                b = m + 1;
            } else if (attackMoments[m] > t) {
                e = m;
            } else {
                return true;
            }
            m = (b + e) / 2;
        }

        return false;
    }

    void fight() {
        iterateEmpire<0>(std::get<0>(ships));
    }

    template<typename S>
    static bool shipDestroyed(const S &ship) {
        return ship.getShield() <= static_cast<typename S::valueType >(0);
    }


    template<size_t i, typename AttackingShipT, typename ShipT, bool isAttacker, int minSpeed, int maxSpeed>
    void iterateRebels(AttackingShipT &enemy, RebelStarship<ShipT, isAttacker, minSpeed, maxSpeed> &ship) {
        //std::cerr << i << "Rebel" << std::endl;

        if (!shipDestroyed(ship)) {
            attack(enemy, ship);

            if (shipDestroyed(ship)) {
                --rebelCount;
            }

        }

        if (!shipDestroyed(enemy)) {
            if constexpr (i + 1 < sizeof...(Args)) {
                iterateRebels<i + 1>(enemy, std::get<i + 1>(ships));
            }
        } else {
            --empireCount;
        }


    }

    template<size_t i, typename AttackingShipT, typename ShipT>
    void iterateRebels(AttackingShipT &enemy, const ShipT &ship) {
        //std::cerr << i << "not Rebel" << std::endl;
        (void) ship; //suppress warning

        if constexpr (i + 1 < sizeof...(Args)) {
            iterateRebels<i + 1>(enemy, std::get<i + 1>(ships));
        }

    }


    template<size_t i, typename ShipT>
    void iterateEmpire(ImperialStarship<ShipT> &ship) {
        //std::cerr << i << "Empire" << std::endl;

        if (!shipDestroyed(ship)) {
            iterateRebels<0>(ship, std::get<0>(ships));

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
        initialFleetCount < 0 > (std::get<0>(ships));
    }

    template<size_t i, typename ShipT>
    void initialFleetCount(const ImperialStarship<ShipT> &ship) {
        if (!shipDestroyed(ship)) {
            ++empireCount;
        }

        if constexpr (i + 1 < sizeof...(Args)) {
            initialFleetCount<i + 1>(std::get<i + 1>(ships));
        }
    }

    template<size_t i, typename ShipT, bool isAttacker, int minSpeed, int maxSpeed>
    void initialFleetCount(const RebelStarship<ShipT, isAttacker, minSpeed, maxSpeed> &ship) {
        if (!shipDestroyed(ship)) {
            ++rebelCount;
        }

        if constexpr (i + 1 < sizeof...(Args)) {
            initialFleetCount<i + 1>(std::get<i + 1>(ships));
        }
    }

    static constexpr size_t howManySquares() {
        size_t result = 0;
        for (T i = static_cast<T>(0); i * i <= t1; i += static_cast<T>(1)) { //todo change?
            ++result;
        }

        return result;
    }


    template<size_t numOfSquares, T ...squares>
    static constexpr std::array<T, numOfSquares + (sizeof...(squares))> calcSquares() {
        constexpr T offset = static_cast<T>(sizeof...(squares));
        constexpr T nextSquare = (offset) * (offset);
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