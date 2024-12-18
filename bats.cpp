#include "bats.hpp"
#include "game.hpp"


void bat::percepts() const {
    std::cout << "You hear wings flapping.\n";
}

bool bat::encounter(game& g) {
    g.set_bat();
    return false;
}