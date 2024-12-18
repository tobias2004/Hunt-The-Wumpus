#ifndef BATS_HPP
#define BATS_HPP

#include <iostream>
#include "event.hpp"
class game;


class bat : public event {
public:


	/*
	* Function: percepts()
	* Description: Prints the event's percept.
	* Side effects: Prints the event's percept to the console.
	*/
    void percepts() const;


    /*
	* Function: encounter(game& g)
	* Description: Sets variable to true.
	* Parameters: 
		* game& g: uses set_bat()
	* Side effects: Sets game's member variable bat.
	* Return: False
	*/
    bool encounter(game& g);

};

#endif
