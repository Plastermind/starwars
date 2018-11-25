//
// Created by piotr on 25.11.18.
//

#ifndef STARWARS_BATTLE_H
#define STARWARS_BATTLE_H

#include <stddef.h>
#include <iostream>
#include "rebelfleet.h"

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

    SpaceBattle<T, t0, t1, Args...> (Args...args) {
        actualTime = t0;
        maxTime = t1;
        std::cout << "lol" << std::endl;
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
private:
    T actualTime;
    T maxTime;
};

#endif //STARWARS_BATTLE_H
