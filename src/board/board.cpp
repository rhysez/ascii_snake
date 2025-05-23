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

void Board::insert_at(int x, int y) {
  if (y < 0 || y >= m_height || x < 0 || x >= m_width) {
    throw std::out_of_range("Board access out of bounds");
  }

  m_board[y][x] = '#';
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
