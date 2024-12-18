#include "wumpus.hpp"
#include "game.hpp"


void wumpus::percepts() const {
    std::cout << "You smell a terrible stench.\n";
}

bool wumpus::encounter(game& g) {
    g.lose_life();
    return false;
}