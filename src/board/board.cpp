#include "board.h"
#include <iostream>
#include <vector>
#include <string>
#include <random>

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

void Board::spawn_fruit() {
  std::random_device rand;
  std::mt19937 gen(rand());
  
  // Generate random ints for board rows and board cols.
  std::uniform_int_distribution<> y_distr(0, m_board.size() - 1);
  std::uniform_int_distribution<> x_distr(0, m_board[0].size() - 1);

  while (true) {
    int y = y_distr(gen);
    int x = x_distr(gen);

    if (m_board[y][x] != '#') {
      m_board[y][x] = 'O';
      break;
    }
  }
}

// Renders the board with latest snake position.
void Board::update_frame() const {
  std::cout << "\n";
  
  for (const auto& row : m_board) {
    for (const auto& cell : row) {
      if (cell == '#') {
        std::cout << "\033[36m" << cell << "\033[0m";
      } else if (cell == 'O') {
        std::cout << "\033[35m" << cell << "\033[0m";
      } else {
        std::cout << "\033[32m" << cell << "\033[0m";
      }
    }
    std::cout << "\n";
  }
  
  std::cout << "\n";
  std::cout << "Score: " << std::to_string(m_score) << "\n";
  std::cout << "Use keys W, A, S, D to move the snake." << "\n";
  std::cout << "Press x to exit the game." << "\n";
}
