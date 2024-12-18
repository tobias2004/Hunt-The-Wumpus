#ifndef WUMPUS_HPP
#define WUMPUS_HPP

#include <iostream>
#include "event.hpp"
class game;

class wumpus : public event {
public:


	/*
	* Function: percepts()
	* Description: Prints the event's percept.
	* Side effects: Prints the event's percept to the console.
	*/
    void percepts() const;


    /*
	* Function: encounter(game& g)
	* Description: Wumpus kills player.
	* Parameters: 
		* game& g: uses lose_life()
	* Side effects: Calls game's member variable lose_life()
	* Return: False
	*/
    bool encounter(game& g);

};
#endif
