#ifndef ROOM_HPP
#define ROOM_HPP

class event; // Forward declaration
class game;  // Forward declaration

// Room interface
class room {
private: 
	event* e;
	char event_type;

public:
	/*
	* Function: room()
	* Description: Constructor for room class.
	*/
	room();


	/*
	* Function: ~room()
	* Description: Destructor for room class.
	*/
	~room();


	/*
	* Function: get_event()
	* Description: Returns the event in the room.
	* Returns: A char indicating the event in the room.
	*/
	char get_event() const;


	/*
	* Function: is_empty()
	* Description: Checks if the room is empty.
	* Returns: True if room is empty, false otherwise.
	*/
	bool is_empty() const;


	/*
	* Function: encounter(game& g)
	* Description: Calls each event's encounter function.
	* Parameters: 
		* game& g: Each encounter function interacts with the game differently.
	* Side effects: Calls the event's encounter function, and it removes the
		event from the board if it's gold or an arrow.
	*/
	void encounter(game& g);


	/*
	* Function: print_percept()
	* Description: Prints a specific event's percept.
	* Side effects: Prints an event's percept to the console.
	*/
	void print_percept() const;


	/*
	* Function: remove_event()
	* Description: Clears the room.
	* Side effects: Deletes dynamic memory of event* and clears room.
	*/
	void remove_event();


	/*
	* Function: set_event(event* new_event, char event_char)
	* Description: Sets an event into an empty room by allocating memory.
	* Parameters:
		* event* new_event: Pointer containing the memory address of the room.
		* char event_char: Character to represent event in room.
	* Side effects: Adds event to room.
	*/
	void set_event(event* new_event, char event_char);
};

#endif
