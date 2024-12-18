#ifndef EVENT_HPP
#define EVENT_HPP

class game; // Forward declaration

// Event interface
class event {
public:


	/*
	* Function: percepts()
	* Description: Prints the event's percept.
	* Side effects: Prints the event's percept to the console.
	*/
	void virtual percepts() const = 0;


	/*
	* Function: encounter(game& g)
	* Description: Each event interacts with the game differently.
	* Parameters: 
		* game& g: Each event interacts with the game differently.
	* Side effects: Each event interacts with the game differently.
	* Return: Returns true if event must be removed from the board,
		false otherwise.
	*/
	bool virtual encounter(game& g) = 0;
};

#endif
