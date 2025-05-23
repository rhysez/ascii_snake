#include <iostream>
#include "board.h"
#include "snake.h"

int main() {
  Board board {60, 20};

  // Example of appending a node.
  Snake snake;

  snake.append(30, 10, board);
  snake.append(30, 11, board);
  snake.append(30, 12, board);

  board.update_frame();
}
