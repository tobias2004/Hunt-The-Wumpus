#include "stalactites.hpp"
#include "game.hpp"


void stalactite::percepts() const {
    std::cout << "You hear water dripping.\n";
}

bool stalactite::encounter(game& g) {
    int random = rand() % 2;
		if (random == 1) {
			g.lose_life();
		}
    return false;
}