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

// nieudolne próby zrobienia battle.h :/



//template <typename T>
//class mypair {
//    T values [2];
//public:
//    mypair (T first, T second)
//    {
//        values[0]=first; values[1]=second;
//    }
//};

//template<typename T>
//class SpaceBattle {
//};

template <typename T, T t0, T t1, typename ...Args>
class SpaceBattle {
public:
    size_t countImperialFleet() {
        return 0;
    }
    size_t countRebelFleet() {
        return 0;
    }
    void tick(T timeStep) {
        actualTime = (actualTime + timeStep) % maxTime;
        print();
    }

    SpaceBattle (Args ...args) : ships(args...) {
        actualTime = t0;
        maxTime = t1;

        //classify<0>(std::get<0>(ships));
        //std::cout << "lol" << std::endl;
        //unpack(args...);
//        unpack(ship, args...);
    }






//    void unpack(S ship, Sargs...args) {
//        std::cout << "kek" << std::endl;
//        unpack(args...);
//    }
//
//    void unpack(S ship) {
//        std::cout << "koniec" << std::endl;
//    }

    // helping function, remember to delete
    void print() {
        std::cout << actualTime << " " << maxTime << std::endl;
    }

    void fight() {
        iterateEmpire<0>(std::get<0>(ships));
    }

public:
    T actualTime;
    T maxTime;
    size_t empireCount;
    size_t rebelCount;


    std::tuple<Args...> ships;

    template <typename S>
    bool shipDestroyed(const S &ship) {
        return ship.getShield() == static_cast<typename S::valueType >(0);
    }


    template<size_t i, typename AttackingShipT, typename ShipT, bool isAttacker, int minSpeed, int maxSpeed>
    void iterateRebels(AttackingShipT &enemy, RebelStarship<ShipT,isAttacker, minSpeed, maxSpeed> &ship) {
        std::cerr << i << "Rebel" << std::endl;

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
    void iterateRebels(AttackingShipT &enemy, ShipT &ship) {
        std::cerr << i << "not Rebel" << std::endl;
        if constexpr (i + 1 < sizeof...(Args)) {
            iterateRebels<i + 1>(enemy, std::get<i + 1>(ships));
        }

    }


    template<size_t i, typename ShipT>
    void iterateEmpire(ImperialStarship<ShipT> &ship) {
        std::cerr << i << "Empire" << std::endl;

        if (!shipDestroyed(ship)) {
            iterateRebels<0>(ship, std::get<0>(ships));

        }
        if constexpr (i + 1 < sizeof...(Args)) {
            iterateEmpire<i + 1>(std::get<i + 1>(ships));
        }

    }

    template<size_t i, typename ShipT>
    void iterateEmpire(ShipT &ship) {
        std::cerr << i << "not Empire" << std::endl;

        if constexpr (i + 1 < sizeof...(Args)) {
            iterateEmpire<i + 1>(std::get<i + 1>(ships));
        }

    }

};



#endif //STARWARS_BATTLE_H
