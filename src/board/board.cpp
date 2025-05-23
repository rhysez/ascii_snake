#include "board.h"
#include <iostream>
#include <vector>

// Represents the game board.
// m_board is initialised with a 2D vector of chars.
Board::Board(int width, int height):
  m_width(width),
  m_height(height),
  m_board(height, std::vector<char>(width, '~'))
{
}

// Renders the board with latest snake position.
void Board::update_frame() const {
  for (const auto& row : m_board) {
    for (const auto& cell : row) {
      std::cout << cell; 
    }
    std::cout << "\n";
  }
}
