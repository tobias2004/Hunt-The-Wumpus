#include <iostream>

#include "game.hpp"
#include "arrow.hpp"
#include "bats.hpp"
#include "escape_rope.hpp"
#include "gold.hpp"
#include "stalactites.hpp"
#include "wumpus.hpp"

// game implementation

game::game(int width, int height, bool debug) :
		width(width),
		height(height),
		debug(debug) {

	this->current_room = rand () % (this->width * this->height);
	this->rope_room = this->current_room;
	this->win = false;
	this->lose = false;
	this->gld = false;
	this->bats = false;
	this->miss_arrow = false;
	this->lives = 3;
	// TODO Create the game board: 2D vector of room objects

	this->rooms = std::vector<std::vector<room>>
		(height, std::vector<room>(width));
	std::vector<std::pair<int, int>> room_numbers;

	int num_rooms = (width * height);

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; ++j) {
            room_numbers.emplace_back(i,j);
        } 
	}

	this->room_coords = room_numbers;

	//allocate 1 rope
	{
		rooms[room_coords[current_room].first][room_coords[current_room].second]
			.set_event(new rope, 'r');
	}
	

	//allocate 1 wumpus
	{
		int room_number = this->get_empty_room();
		this->wumpus_room = room_number;
		rooms[room_coords[room_number].first][room_coords[room_number].second]
			.set_event(new wumpus, 'w');
	}

	//allocate 2 bats
	for (int i = 0; i < 2; i++) {
		int room_number = this->get_empty_room();
		rooms[room_coords[room_number].first][room_coords[room_number].second]
			.set_event(new bat, 'b');
	}

	//allocate 2 stalactites
	for (int i = 0; i < 2; i++) {
		int room_number = this->get_empty_room();
		rooms[room_coords[room_number].first][room_coords[room_number].second]
			.set_event(new stalactite, 's');
	}

	//allocate 2 arrows
	for (int i = 0; i < 2; i++) {
		int room_number = this->get_empty_room();
		rooms[room_coords[room_number].first][room_coords[room_number].second]
			.set_event(new arrow, 'a');
	}

	//allocate 1 gold
	{
		int room_number = this->get_empty_room();
		rooms[room_coords[room_number].first][room_coords[room_number].second]
			.set_event(new gold, 'g');
	}
}

void game::display_game() const{

	std::cout << std::endl << std::endl;
	std::cout << "Gold: " << this->gld << std::endl;
	std::cout << "Lives: " << this->lives << std::endl;
	std::cout << "Arrows remaining: " << this->num_arrows << std::endl;

	std::string row_border = "--";
	for (int i = 0; i < this->width; ++i) {
		row_border += "-----";
	}

	std::cout << row_border << std::endl;

	for (int i = 0; i < this->height; ++i) {
		std::cout << "||";

		for (int j = 0; j < this->width; ++j) {
			int room_num = (width * i) + j;

			if (room_num == current_room) {
				std::cout << "*";
			}
			else if ((rooms[i][j].is_empty()) || !debug) {
				std::cout << " ";
			}
			else {
				std::cout << rooms[i][j].get_event();
			}

			std::cout << " ||";
		}
		std::cout << std::endl;
		std::cout << row_border << std::endl;
	}

	//example output (when finished): 
	// ----------------------
	// || P || G || P ||   ||
	// ----------------------
	// ||   || W ||   || S ||
	// ----------------------   
	// ||   ||   ||   || S ||
	// ----------------------   
	// ||*  ||   ||   ||   ||
	// ----------------------
}


bool game::is_direction(char c) {
	return c == 'w' ||
		c == 'a' ||
		c == 's' ||
		c == 'd';
}

char game::to_lower(char direction) {
	if (direction >= 'A' && direction <= 'Z') {
		return direction + ('a' - 'A');
	}
	return direction;
}

bool game::can_move_in_direction(char direction) {
	if (direction == 'a') {
		if (this->current_room % this->width == 0) {
			return false;
		}
	}
	if (direction == 'w') {
		if (this->current_room < this->width) {
			return false;
		}
	}
	if (direction == 'd') {
		if (this->current_room % this->width == (this->width - 1)) {
			return false;
		}
	}
	if (direction == 's') {

		if (this->current_room>=((this->width * this->height) - this->width)) {
			return false;
		}
	}
	return true;
}

bool game::is_valid_action(char action) {
	if (this->is_direction(action)) {
		char direction = action;
		return this->can_move_in_direction(direction);
	} else if (action == 'f') {
		return this->num_arrows > 0;
	}
	return false;
}

void game::print_action_error(char action) {
	if (this->is_direction(action)) {
		std::cout << "You can't move in that direction!" << std::endl <<
			std::endl;
	} else if (action == 'f') {
		std::cout << "You're out of arrows!" << std::endl << std::endl;
	} else {
		std::cout << std::endl << "That's an invalid input!" << std::endl
			<< std::endl;
	}
}

char game::get_player_action() {
	char action;
	bool first = true;
	do {
		if (!first) {
			char previous_action = action;
			this->print_action_error(previous_action);
		}
		first = false;

		std::cout << std::endl << std::endl << "What would you like to do?" <<
			std::endl << std::endl;
		std::cout << "w: move up" << std::endl;
		std::cout << "a: move left" << std::endl;
		std::cout << "s: move down" << std::endl;
		std::cout << "d: move right" << std::endl;
		std::cout << "f: fire an arrow" << std::endl;

		std::cin >> action;
		action = this->to_lower(action);
	} while (!this->is_valid_action(action));

	return action;
}

char game::get_arrow_fire_direction() {
	char direction;
	bool first = true;
	do {
		if (!first) {
			std::cout << std::endl << "That's an invalid input!" <<
				std::endl << std::endl;
		}
		first = false;

		std::cout << std::endl << std::endl <<
			"What direction would you like to fire the arrow?" << std::endl <<
			std::endl;
		std::cout << "w: up" << std::endl;
		std::cout << "a: left" << std::endl;
		std::cout << "s: down" << std::endl;
		std::cout << "d: right" << std::endl;

		std::cin >> direction;
		direction = this->to_lower(direction);
	} while (!this->is_direction(direction));

	return direction;
}

void game::move_up() {
	this->current_room -= width;
}

void game::move_down() {
	this->current_room += width;
}

void game::move_left() {
	this->current_room -= 1;
}

void game::move_right() {
	this->current_room += 1;
}

void game::move(char direction) {
	if (direction == 'w') {
		this->move_up();
	} else if (direction == 'a') {
		this->move_left();
	} else if (direction == 's') {
		this->move_down();
	} else {
		this->move_right();
	}
}

void game::fire_arrow_left() {
	int arrow_position = this->current_room;

	// arrow travels 3 rooms
	for (int i = 0; i < 3; i++) {
		this->check_missed_arrow(arrow_position);

		// arrow hits wall
		if ((arrow_position % width) == 0) {
			
			// arrow hit wumpus
			if (arrow_position == this->wumpus_room) {
				this->win = true;
			}
			if (this->miss_arrow) {
				this->missed_arrow();
				this->miss_arrow = false;
			}
			return;
			
		}
		arrow_position -= 1;

		if (arrow_position == this->wumpus_room) {
			this->win = true;
			this->miss_arrow = false;
			return;
		}
	}
	// drop arrow if it missed everything
	this->drop_arrow(arrow_position);
	this->check_missed_arrow(arrow_position);

	// arrow missed wumpus
	if (this->miss_arrow) {
		this->missed_arrow();
		this->miss_arrow = false;
	}
}

void game::fire_arrow_right() {
	int arrow_position = this->current_room;

	// arrow travels 3 rooms
	for (int i = 0; i < 3; i++) {
		this->check_missed_arrow(arrow_position);

		// arrow hit wall
		if ((arrow_position % width) == (width - 1)) {

			// arrow killed wumpus
			if (arrow_position == this->wumpus_room) {
			this->win = true;
			}
			if (this->miss_arrow) {
				this->missed_arrow();
				this->miss_arrow = false;
			}
			return;
			
		}
		arrow_position += 1;

		if (arrow_position == this->wumpus_room) {
			this->win = true;
			return;
		}

		if (this->miss_arrow) {
			this->missed_arrow();
			this->miss_arrow = false;
		}
	}
	// drop arrow if it missed everything
	this->drop_arrow(arrow_position);
	this->check_missed_arrow(arrow_position);

	// wumpus woke up
	if (this->miss_arrow) {
		this->missed_arrow();
		this->miss_arrow = false;
	}
}

void game::fire_arrow_up() {
	int arrow_position = this->current_room;

	// arrow travels 3 rooms
	for (int i = 0; i < 3; i++) {
		this->check_missed_arrow(arrow_position);

		// arrow hits wall
		if (arrow_position < width) {

			// arrow hits wumpus
			if (arrow_position == this->wumpus_room) {
			this->win = true;
			}
			if (this->miss_arrow) {
				this->missed_arrow();
				this->miss_arrow = false;
			}
			return;
			
		}
		arrow_position -= width;

		if (arrow_position == this->wumpus_room) {
			this->win = true;
			return;
		}
	}
	// drop arrow if it missed everything
	this->drop_arrow(arrow_position);
	this->check_missed_arrow(arrow_position);

	// wumpus woke up
	if (this->miss_arrow) {
		this->missed_arrow();
		this->miss_arrow = false;
	}
}

void game::fire_arrow_down() {
	int arrow_position = this->current_room;

	// arrow travels 3 rooms
	for (int i = 0; i < 3; i++) {
		this->check_missed_arrow(arrow_position);

		// arrow hits wall
		if ((arrow_position + width) >= room_coords.size()) {

			// arrow hits wumpus
			if (arrow_position == this->wumpus_room) {
			this->win = true;
			}
			if (this->miss_arrow) {
				this->missed_arrow();
				this->miss_arrow = false;
			}
			return;
			
		}
		arrow_position += width;

		if (arrow_position == this->wumpus_room) {
			this->win = true;
			return;
		}
	}
	// drop arrow if it missed everything
	this->drop_arrow(arrow_position);
	this->check_missed_arrow(arrow_position);

	// wumpus woke up
	if (this->miss_arrow) {
		this->missed_arrow();
		this->miss_arrow = false;
	}
}

void game::fire_arrow(char direction) {
	if (direction == 'w') {
		this->fire_arrow_up();
	} else if (direction == 'a') {
		this->fire_arrow_left();
	} else if (direction == 'd') {
		this->fire_arrow_right();
	} else {
		this->fire_arrow_down();
	}

	this->num_arrows--;
}

void game::set_bat() {
	this->bats = true;
}

bool game::get_gold() const{
	return this->gld;
}

void game::set_gold() {
	this->gld = true;
}

void game::set_win() {
	this->win = true;
}

void game::add_arrow() {
	this->num_arrows++;
}


void game::print_percepts() const {
	//room right
	if (room_coords[this->current_room].second + 1 < width) {
		const room* right = &rooms[room_coords[this->current_room].first]
			[room_coords[this->current_room].second+1];
		if (!right->is_empty()) {
			right->print_percept();
		}
	}
	//room left
	if (room_coords[this->current_room].second - 1 >= 0) {
		const room* left = &rooms[room_coords[this->current_room].first]
			[room_coords[this->current_room].second-1];
		if (!left->is_empty()) {
			left->print_percept();
		}
	}
	//room down
	if (room_coords[this->current_room].first + 1 < height) {
		const room* down = &rooms[room_coords[this->current_room].first+1]
			[room_coords[this->current_room].second];
		if (!down->is_empty()) {
			down->print_percept();
		}
	}
	//room up
	if (room_coords[this->current_room].first - 1 >= 0) {
		const room* up = &rooms[room_coords[this->current_room].first-1]
			[room_coords[this->current_room].second];
		if (!up->is_empty()) {
			up->print_percept();
		}
	}
}


bool game::check_lose() const {
	if (this->lives == 0) {
		return true;
	}
	return false;
}


void game::lose_life() {
	std::cout << "You lost a life! Returning to rope room." << std::endl;
	this->lives--;
	this->current_room = rope_room;

	//scatter arrows
	for (int i = 0; i < this->num_arrows; i++) {
		int random = this->get_empty_room();

		rooms[this->room_coords[random].first][this->room_coords[random].second]
			.set_event(new arrow, 'a');
	}
	this->num_arrows = 0;
	
	//scatter gold
	if (this->gld) {
		int random = this->get_empty_room();

		rooms[this->room_coords[random].first][this->room_coords[random].second]
			.set_event(new gold, 'g');

		this->gld = false;
	}
}


char game::bat_effect() {
	this->bats = false;
	int random  = rand() % 4;

	if (random == 0) {
		return 'a';
	}
	else if (random == 1) {
		return 'w';
	}
	else if (random == 2) {
		return 'd';
	}
	return 's';
}


int game::get_empty_room() const {
	int random;
	do {
		random = rand() % room_coords.size();
	} while (!rooms[this->room_coords[random].first][this->room_coords[random]
		.second].is_empty());

	return random;
}


void game::check_missed_arrow(int arrow_room) {
	//room right
	if (room_coords[arrow_room].second + 1 < width) {
		room* right = &rooms[room_coords[arrow_room].first]
			[room_coords[arrow_room].second+1];
		if (right->get_event() == 'w') {
			this->miss_arrow = true;
		}
	}
	//room left
	if (room_coords[arrow_room].second - 1 >= 0) {
		room* left = &rooms[room_coords[arrow_room].first]
			[room_coords[arrow_room].second-1];
		if (left->get_event() == 'w') {
			this->miss_arrow = true;
		}
	}
	//room down
	if (room_coords[arrow_room].first + 1 < height) {
		room* down = &rooms[room_coords[arrow_room].first+1]
			[room_coords[arrow_room].second];
		if (down->get_event() == 'w') {
			this->miss_arrow = true;
		}
	}
	//room up
	if (room_coords[arrow_room].first - 1 >= 0) {
		room* up = &rooms[room_coords[arrow_room].first-1]
			[room_coords[arrow_room].second];
		if (up->get_event() == 'w') {
			this->miss_arrow = true;
		}
	}

}


void game::missed_arrow() {
	rooms[room_coords[this->wumpus_room].first]
		[room_coords[this->wumpus_room].second].remove_event();
	int random = this->get_empty_room();
	rooms[room_coords[random].first][room_coords[random].second]
		.set_event(new wumpus, 'w');
	this->wumpus_room = random;
	std::cout << "You have awakened the wumpus!\n";
}


void game::drop_arrow(int arrow_room) {
	if (rooms[room_coords[arrow_room].first]
		[room_coords[arrow_room].second].is_empty()) {
		rooms[room_coords[arrow_room].first]
			[room_coords[arrow_room].second].set_event(new arrow, 'a');
	}
	else {
		int random = this->get_empty_room();
		rooms[room_coords[random].first][room_coords[random].second]
			.set_event(new arrow, 'a');
	}

}


void game::play_game() {
	while (!this->win && !this->check_lose()) {
		// Print game board
		this->display_game();

		// Display precepts around player's location
		this->print_percepts();

		//Get input from user
		char action = this->get_player_action();

		// Process action
		if (this->is_direction(action)) {
			// W/A/S/D = move player
			char direction;
			//If under bat effect, randomize movement
			if (bats) {
				do {
					direction = this->bat_effect();
				} while (!this->can_move_in_direction(direction));
			}
			else {
				direction = action;
			}
			this->move(direction);
		} else {
			// F = prompt for arrow fire direction and fire arrow
			char direction = this->get_arrow_fire_direction();
			this->fire_arrow(direction);
		}

		room* current_room = &rooms[room_coords[this->current_room].first]
			[room_coords[this->current_room].second];

		//If the room isn't empty, perform room event.
		if (!current_room->is_empty()) {
			current_room->encounter(*this);
			}

		}

	if (this-> win == true) {
		std::cout << "You won!\n";
	}
	else {
		std::cout << "You lost!\n";
	}
}
