#include <iostream>
#include "board.h"
#include "snake.h"

int main() {
  Board board {60, 20};

  // Example of appending a node.
  Snake snake;

  snake.spawn(30, 10, board);
  
  board.update_frame();
}
