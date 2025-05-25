#include "board.h"
#include <iostream>
#include <vector>
#include <string>

// Represents the game board.
// m_board is initialised with a 2D vector of chars.
Board::Board(int height, int width):
  m_height(height),
  m_width(width),
  m_board(height, std::vector<char>(width, '~')),
  m_score(0)
{
}

void Board::insert_at(int y, int x) {
  m_board[y][x] = '#';
}

void Board::delete_at(int y, int x) {
  m_board[y][x] = '~';
}

// Renders the board with latest snake position.
void Board::update_frame() const {
  std::cout << "\n";
  
  for (const auto& row : m_board) {
    for (const auto& cell : row) {
      std::cout << cell; 
    }
    std::cout << "\n";
  }
  
  std::cout << "\n";
  std::cout << "Score: " << std::to_string(m_score) << "\n";
}
