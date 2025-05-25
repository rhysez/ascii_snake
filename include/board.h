#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>

// Represents the game board, contains:
// Integers that represent the width and height.
// 2D vector of chars that represents the actual board.
class Board {
  private:
    int m_height;
    int m_width;
    std::vector<std::vector<char>> m_board;

  public:
    Board(int height, int width);

    int get_width() const {
      return m_width;
    }

    int get_height() const {
      return m_height;
    }

    int get_total_cells() const {
      return m_width * m_height;
    }

    void insert_at(int y, int x);
    void delete_at(int y, int x);

    std::vector<std::vector<char>> get_board() const {
      return m_board;
    }

    void update_frame() const;

    int board_x_size() const {
      return m_board[0].size();
    }

    int board_y_size() const {
      return m_board.size();
    }
};

#endif // BOARD_H


