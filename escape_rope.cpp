#include "escape_rope.hpp"
#include "game.hpp"

void rope::percepts() const {

}

bool rope::encounter(game& g) {
    if (g.get_gold()) {
        g.set_win();
    }
    return false;
}