# ascii_snake

### Project overview
A game of snake that can be played within a terminal's shell session. The player can move the snake using the W, A, S and D keys. The goal of the game is to eat as many fruits as possible - for each fruit the snake consumes, the snake grows by one 'node'. If the snake's head touches its own body, the game is over.

### Minimal abstractions
I wanted to build snake in its most primitive form - in the terminal using only ASCII characters. So, as you'd expect, everything in this game is ASCII. The game is comprised of three main systems - vectors, linked lists, and a linear search algorithm to navigate lists. I wanted to build the game with as little help from libraries as possible. This approach forced me to get into the weeds of fundamental C++ concepts.

The only third party library that ascii_snake uses is termios for keyboard input detection in non canonical mode.
