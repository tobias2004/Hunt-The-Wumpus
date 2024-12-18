#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <utility>

#include "room.hpp"


// game interface
class game {
private:
	// TODO declare a 2D vector of Room objects:
	std::vector<std::vector<room>> rooms;
	std::vector<std::pair<int,int>> room_coords;

	// Suggested member variables:
	int num_arrows = 0; 	// keep track of number of arrows remaining
	int width;				// width of the game grid
	int height;				// height of the game grid
	bool debug;				// debug mode or not
	int current_room;       // holds the current room number
	int wumpus_room;        // holds the wumpus' room number
	int rope_room;          // holds the rope's room number
	int lives;              // lives left
	bool win;               // player wins
	bool lose;              // player loses
	bool gld;               // has gold
	bool bats;              // bat event 
	bool miss_arrow;        // wakes up wumpus

public:
	// Suggested functions (there are no required functions here):
	
	/*
	 * Function: Constructor
	 * Description: Constructs game object with a grid matching the given
	 * 		width and height
	 * Parameters:
	 * 		width (int): Width of the grid
	 * 		height (int): Height of the grid
	 * 		debug (bool): Whether or not debug mode should be enabled
	 */
	game(int width, int height, bool debug);

	/*
	 * Function: display_game
	 * Description: Displays the game grid in the terminal
	 */
	void display_game() const;


	/*
	 * Function: is_direction
	 * Description: Returns true if the given character is a valid direction
	 * 		character (w/a/s/d) and false otherwise
	 * Parameters:
	 * 		c (char): The character to check
	 * Returns (bool): Boolean indicating whether the character is a valid
	 * 		direction character (w/a/s/d)
	 */
	bool is_direction(char c);

	/*
	 * Function: to_lower
	 * Description: Converts a given character to lowercase. Used to standard
	 * 		a user's character input.
	 * Parameters:
	 * 		direction (char): Character to convert to lowercase
	 * Returns (char): Character converted to lowercase
	 */
	char to_lower(char direction);

	/*
	 * Function: can_move_in_direction
	 * Description: Determines whether the player can move in the given
	 * 		direction, based on their current location and the size of the
	 * 		grid.
	 * Parameters:
	 * 		direction (char): Direction the player wishes to move in
	 * Returns (bool): True if the player can move in the given direction
	 * 		without moving off the grid. False otherwise.
	 */
	bool can_move_in_direction(char direction);

	/*
	 * Function: is_valid_action
	 * Description: Determines whether the given action is valid.
	 * Parameters:
	 * 		action (char): Action the player wishes to perform.
	 * Returns (bool): True if the requested action is valid. False otherwise.
	 */
	bool is_valid_action(char action);

	/*
	 * Function: print_action_error
	 * Description: Prints a clear error message associated with the user's
	 * 		provided invalid action
	 * Parameters:
	 * 		action (char): Invalid action that the user requested
	 */
	void print_action_error(char action);

	/*
	 * Function: get_player_action
	 * Description: Prompts the player for their action for the turn and
	 * 		returns it as a char (w, a, s, d, or f). If the player enters
	 * 		an invalid action, this function reprompts until a valid one is
	 * 		provided.
	 * Returns (char): The valid action provided by the player.
	 */
	char get_player_action();

	/*
	 * Function: get_arrow_fire_direction
	 * Description: Prompts the player for the direction they want to fire an
	 * 		arrow (w, a, s, or d) and returns it as a char. If player enters
	 * 		an invalid direction, this function reprompts until a valid one is
	 * 		provided.
	 * Returns (char): The valid direction provided by the player.
	 */
	char get_arrow_fire_direction();

	/*
	 * Function: move_up
	 * Description: Moves the player up one grid space
	 * Pre-condition: Player is capable of moving in this direction (without
	 * 		hitting the edge of the board)
	 * Post-condition: Player is moved accordingly.
	 */
	void move_up();

	/*
	 * Function: move_down
	 * Description: Moves the player down one grid space
	 * Pre-condition: Player is capable of moving in this direction (without
	 * 		hitting the edge of the board)
	 * Post-condition: Player is moved accordingly.
	 */
	void move_down();

	/*
	 * Function: move_left
	 * Description: Moves the player left one grid space
	 * Pre-condition: Player is capable of moving in this direction (without
	 * 		hitting the edge of the board)
	 * Post-condition: Player is moved accordingly.
	 */
	void move_left();

	/*
	 * Function: move_right
	 * Description: Moves the player right one grid space
	 * Pre-condition: Player is capable of moving in this direction (without
	 * 		hitting the edge of the board)
	 * Post-condition: Player is moved accordingly.
	 */
	void move_right();

	/*
	 * Function: move
	 * Description: Moves the player in the direction specified by the given
	 * 		character
	 * Parameters:
	 * 		direction (char): Direction in which to move the player (a for
	 * 			west, s for south, d for east, w for north).
	 * Pre-condition: Player is capable of moving in this direction (without
	 * 		hitting the edge of the board)
	 * Post-condition: Player is moved accordingly.
	 */
	void move(char direction);

	/*
	 * Function: fire_arrow_up
	 * Description: Fires an arrow upward
	 * Post-condition: Arrow is fired upward. Wumpus is killed if hit / moves
	 * 		if missed.
	 */
	void fire_arrow_up();

	/*
	 * Function: fire_arrow_down
	 * Description: Fires an arrow downward
	 * Post-condition: Arrow is fired downward. Wumpus is killed if hit / moves
	 * 		if missed.
	 */
	void fire_arrow_down();

	/*
	 * Function: fire_arrow_left
	 * Description: Fires an arrow leftward
	 * Post-condition: Arrow is fired leftward. Wumpus is killed if hit / moves
	 * 		if missed.
	 */
	void fire_arrow_left();

	/*
	 * Function: fire_arrow_right
	 * Description: Fires an arrow rightward
	 * Post-condition: Arrow is fired rightward. Wumpus is killed if hit/ moves
	 * 		if missed.
	 */
	void fire_arrow_right();

	/*
	 * Function: fire_arrow
	 * Description: Fires an arrow in the direction specified by the given
	 * 		character
	 * Parameters:
	 * 		direction (char): Direction in which to fire arrow (a for
	 * 			west, s for south, d for east, w for north).
	 * Post-condition: Arrow is fired. Wumpus is killed if hit and moves if
	 * 		missed.
	 */
	void fire_arrow(char direction);


	/*
	* Function: print_percepts()
	* Description: Checks if there are events adjacent, and prints their
		percepts.
	* Side effects: Prints percepts to the console.
	*/
	void print_percepts() const;


	/*
	* Function: check_lose()
	* Description: Checks if player died by wumpus or stalactites.
	* Returns: True if player dies, false otherwise.
	*/
	bool check_lose() const;


	/*
	* Function: lose_life()
	* Description: Called when player is killed. Decrements lives by 1.
	* Side effects: Decrements lives memeber variable by 1.
	*/
	void lose_life();


	/*
	* Function: bat_effect()
	* Description: Called when bat is set to true. Returns a random direction.
	* Returns: A random direction.
	*/
	char bat_effect();


	/*
	* Function: set_bat()
	* Description: Setter for the bat member variable.
	* Side effects: Sets member variable bat to true.
	*/
	void set_bat();


	/*
	* Function: get_gold()
	* Description: Returns the status of the gold variable.
	* Returns: Status of the gold variable.
	*/
	bool get_gold() const;


	/*
	* Function: set_gold()
	* Description: Setter for the gold variable.
	* Side effects: Sets boolean variable gold when called.
	*/
	void set_gold();


	/*
	* Function: set_win()
	* Description: Will set a boolean variable win. Called if the player wins.
	* Side effects: Sets the member variable win.
	*/
	void set_win();
	

	/*
	* Function: add_arrow()
	* Description: Add an arrow to the player's inventory.
	* Side effects: Will add 1 to the num_arrows member variable.
	*/
	void add_arrow();


	/*
	* Function: get_empty_room()
	* Description: Generates random numbers until it finds an empty room.
	* Returns: Room number of empty room.
	*/
	int get_empty_room() const;


	/*
	* Function: check_missed_arrow(int arrow_room)
	* Description: Checks if the arrow missed the wumpus.
	* Parameters: 
		* int arrow_room: Room number to check if next to wumpus.
	* Side effects: Will set a boolean variable miss_wumpus.
	*/
	void check_missed_arrow(int arrow_room);


	/*
	* Function: missed_arrow()
	* Description: Awakens the wompus, and moves it to a random empty room.
	* Side effects: Removes wumpus from current room, adds it to random room.
	*/
	void missed_arrow();


	/*
	* Function: drop_arrow(int arrow_room)
	* Description: Will drop an arrow in the room it lands in. If that room has
		an event, it will drop in a random empty room.
	* Parameters: 
		* int arrow_room: Room number for arrow to be dropped.
	* Side effects: Add arrow event to room where arrow lands. 
	*/
	void drop_arrow(int arrow_room);


	/*
	 * Function: play_game
	 * Description: Runs one full iteration of the game
	 */
	void play_game();
};
#endif
