#include "room.hpp"
#include "event.hpp"
#include "game.hpp"

room::room() {
    this->e = nullptr;
    this->event_type = 'e';
}


room::~room() {
    if (e != nullptr) {
        delete this->e;
        this->e = nullptr;
        this->event_type = 'e';
    }
}


char room::get_event() const {
    return this->event_type;
}


bool room::is_empty() const {
    if (this->event_type == 'e') {
        return true;
    }
    else {
        return false;
    }
}


void room::encounter(game& g) {
    if (e->encounter(g)) {
        delete this->e;
        this->e = nullptr;
        this->event_type = 'e';
    }
}

void room::print_percept() const {
    this->e->percepts();
}


void room::remove_event() {
    delete this->e;
    this->e = nullptr;
    this->event_type = 'e';

}


void room::set_event(event* new_event, char event_char) {
    this->e = new_event;
    this->event_type = event_char;
}