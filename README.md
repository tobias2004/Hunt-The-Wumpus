# Hunt the Wumpus

Hunt the Wumpus is a C++ text-based adventure game where players explore a grid-based cave to find gold, avoid hazards, and outsmart the Wumpus. This project is part of a CS 162 assignment designed to reinforce object-oriented programming and software engineering principles.

## Features

- **Dynamic Grid-Based Cave:** User-defined cave dimensions with randomized placement of events.
- **Core Game Elements:**
  - **Wumpus:** Avoid or slay the Wumpus to win.
  - **Gold:** Find and collect hidden gold.
  - **Super Bats:** Bats can randomly displace you.
  - **Stalactites:** Enter at your own risk with a 50% chance of survival.
  - **Arrows:** Collect arrows to attack the Wumpus.
- **Debug Mode:** Option to visualize all event locations for testing and debugging.
- **Game Logic:** Implemented using polymorphic classes for each event type.
- **Player Lives:** The adventurer starts with three lives. Losing all lives ends the game.

## Technologies and Concepts

- **Object-Oriented Programming (OOP):** Includes inheritance, polymorphism, and abstract classes.
- **Standard Template Library (STL):** Utilized `std::vector` for cave representation.
- **File Separation:** Clean code organization with headers and implementation files.
- **Memory Safety:** No memory leaks ensured through careful dynamic allocation and proper destructors.

## How to Play

1. Launch the program.
2. Define the cave's width and height (between 4 and 30).
3. Choose debug mode (1 for enabled, 0 for disabled).
4. Navigate the cave using WASD keys:
   - `W`: Move north.
   - `A`: Move west.
   - `S`: Move south.
   - `D`: Move east.
   - `F`: Fire an arrow.
5. Use percepts to detect nearby events and avoid hazards.

### Winning Conditions

- Slay the Wumpus using arrows.
- Collect the gold and return to the starting point.

### Losing Conditions

- Lose all three lives due to hazards or the Wumpus.
