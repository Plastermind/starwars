//
// Created by piotr on 25.11.18.
//

#include "rebelfleet.h"
#include "imperialfleet.h"

#include <iostream>

int main() {
    XWing<int> xwing(1, 299796, 1);
    DeathStar<int> deathStar(1, 1);


    Explorer<int> explorer(1, 299796);
    ImperialDestroyer<int> imperialDestroyer(1, 1);

    std::cout << deathStar.getShield() << " " << xwing.getShield() << std::endl;
    attack<DeathStar<int>, XWing<int>>(deathStar, xwing);
    std::cout << deathStar.getShield() << " " << xwing.getShield() << std::endl;

    std::cout << std::endl;

    std::cout << imperialDestroyer.getShield() << " " << explorer.getShield() << std::endl;
    attack<ImperialDestroyer<int>, Explorer<int>>(imperialDestroyer, explorer);
    std::cout << imperialDestroyer.getShield() << " " << explorer.getShield() << std::endl;

    return 0;
}
