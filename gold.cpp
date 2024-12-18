#include "gold.hpp"
#include "game.hpp"


void gold::percepts() const {
    std::cout << "You see something shimmer nearby.\n";
}

bool gold::encounter(game& g) {
    g.set_gold();
    return true;
}