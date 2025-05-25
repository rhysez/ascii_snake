# ascii_snake

### Project overview
A game of snake that can be played within a terminal's shell session. The player can move the snake using the W, A, S and D keys. The goal of the game is to eat as many fruits as possible - for each fruit the snake consumes, the snake grows by one 'node'. If the snake's head touches its own body, the game is over.

### Minimal abstractions
I wanted to build snake in its most primitive form - in the terminal using only ASCII characters. So, as you'd expect, everything in this game is ASCII. The game is comprised of three main systems - vectors, linked lists, and a linear search algorithm to navigate lists. I wanted to build the game with as little help from libraries as possible. This approach forced me to get into the weeds of fundamental C++ concepts.

The only third party library that ascii_snake uses is termios for keyboard input detection in non canonical mode.

### Data structures, algorithms and game logic
In order to build a grid that the snake can freely move around in, I decided to use a **two-dimensional vector**. This allowed me to create 'rows' and 'cols'. This meant that navigating the grid was conceptually quite straightforward:
 - Moving left requires the snake's head to shift one index backwards in the current sub-vector.
 - Moving right requires the snake's head to shift one index forwards in the current sub-vector.
 - Moving up requires the snake's head to traverse into the same index in the previous sub-vector.
 - Moving down requires the snake's head to traverse into the same index in the next sub-vector.

The snake itself is a **linked list** of `SnakeNode` class type objects, with each `SnakeNode` storing it's co-ordinates in the grid and a pointer to the `next` or `prev` node.

When the snake wants to move, the program recursively iterates through each `SnakeNode` and carries out the following algorithm:
 1. Store node's current co-ordinates as the 'previous' co-ordinates (where the node is moving _from_) in memory.
 2. Store the co-ordinates of where the node _wants_ to go as the new 'current' co-ordinates in memory.
 3. Insert '#' character in the grid at the node's new co-ordinates.
 4. Insert '~' character in the grid at the node's previous co-ordinates.

