#ifndef STALACTITES_HPP
#define STALACTITES_HPP

#include <iostream>
#include "event.hpp"
class game;


class stalactite : public event {
public:


	/*
	* Function: percepts()
	* Description: Prints the event's percept.
	* Side effects: Prints the event's percept to the console.
	*/
    void percepts() const;


    /*
	* Function: encounter(game& g)
	* Description: Randomizes if player is killed or not.
	* Parameters: 
		* game& g: uses lose_life()
	* Side effects: If player is killed, calls the lose_life() function.
	* Return: False
	*/
    bool encounter(game& g);

};

#endif
