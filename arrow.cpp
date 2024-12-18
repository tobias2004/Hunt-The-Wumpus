#include "arrow.hpp"
#include "game.hpp"


void arrow::percepts() const {
    std::cout << "You see an arrow on the ground in an adjacent room.\n";
}

bool arrow::encounter(game& g) {
    g.add_arrow();
    return true;
}