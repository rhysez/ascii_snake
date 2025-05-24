#include <iostream>
#include "board.h"
#include "snake.h"

int main() {
  Board board {20, 60};
  Snake snake;
  snake.spawn(18, 30, board);
  
  snake.append(board);
  snake.append(board);
  snake.append(board);
  snake.append(board);
  snake.append(board);
  snake.append(board);
  snake.append(board);
  snake.append(board);
  snake.append(board);
  snake.append(board);
  snake.append(board);
  snake.append(board);
  snake.append(board);
  snake.append(board);
}
