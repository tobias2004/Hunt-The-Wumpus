#ifndef ESCAPE_ROPE_HPP
#define ESCAPE_ROPE_HPP

#include "event.hpp"
class game;


class rope : public event {
public:


	/*
	* Function: percepts()
	* Description: Prints the event's percept.
	* Side effects: Prints the event's percept to the console.
	*/
    void percepts() const;


    /*
	* Function: encounter(game& g)
	* Description: Checks if player returns with gold and wins the game.
	* Parameters: 
		* game& g: uses get_gold() and set_win()
	* Side effects: Sets game member variable win if player returns with gold.
	* Return: False
	*/
    bool encounter(game& g);

};
#endif
