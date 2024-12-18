#ifndef ARROW_HPP
#define ARROW_HPP

#include <iostream>
#include "event.hpp"
class game;


class arrow : public event {
public:


	/*
	* Function: percepts()
	* Description: Prints the event's percept.
	* Side effects: Prints the event's percept to the console.
	*/
    void percepts() const;


    /*
	* Function: encounter(game& g)
	* Description: Adds one arrow to the player's inventory.
	* Parameters: 
		* game& g: uses add_arrow()
	* Side effects: Adds 1 to game's member variable num_arrows.
	* Return: True
	*/
    bool encounter(game& g);

};

#endif
