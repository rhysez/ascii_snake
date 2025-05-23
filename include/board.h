#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>

// Represents the game board, contains:
// Integers that represent the width and height.
// 2D vector of chars that represents the actual board.
class Board {
  private:
    int m_width;
    int m_height;
    std::vector<std::vector<char>> m_board;

  public:
    Board(int width, int height);

    int get_width() const {
      return m_width;
    }

    int get_height() const {
      return m_height;
    }

    int get_total_cells() const {
      return m_width * m_height;
    }

    void insert_at(int x, int y);

    std::vector<std::vector<char>> get_board() const {
      return m_board;
    }

    void update_frame() const; 
};

#endif // BOARD_H


