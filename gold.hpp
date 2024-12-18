#ifndef GOLD_HPP
#define GOLD_HPP

#include <iostream>
#include "event.hpp"
class game;


class gold : public event {
public:


	/*
	* Function: percepts()
	* Description: Prints the event's percept.
	* Side effects: Prints the event's percept to the console.
	*/
    void percepts() const;


    /*
	* Function: encounter(game& g)
	* Description: Adds the gold to the player's inventory.
	* Parameters: 
		* game& g: uses set_gold()
	* Side effects: Sets game's member variable gold.
	* Return: True.
	*/
    bool encounter(game& g);

};

#endif
