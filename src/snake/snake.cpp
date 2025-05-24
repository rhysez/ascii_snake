#include "snake.h"
#include "snake_node.h"
#include "board.h"
#include <iostream>

Snake::Snake() : m_head(nullptr), m_tail(nullptr) {}

// Creates the initial head node at the start of the game.
// Takes a reference to the Board type object.
void Snake::spawn(int y_pos, int x_pos, Board& board) {
  SnakeNode* head_node = new SnakeNode(y_pos, x_pos);
  
  m_head = m_tail = head_node; 

  board.insert_at(y_pos, x_pos);
  board.update_frame();
}

// Creates a new node and appends to the end of the snake as the new tail.
// Need to insert the node at the row/col next to the current node.
void Snake::append(Board& board) {
    int tail_x_pos = m_tail->get_x_index();
    int tail_y_pos = m_tail->get_y_index();

    // Co-ordinates for the new node, relative to the tail.
    int x_pos;
    int y_pos;

    char safe_cell = '~';

    // Surrounding cells.
    // Used for checking where the node can be safely appended.
    char cell_up = board.get_board()[tail_y_pos - 1][tail_x_pos];
    char cell_down = board.get_board()[tail_y_pos + 1][tail_x_pos];
    char cell_left = board.get_board()[tail_y_pos][tail_x_pos - 1];
    char cell_right = board.get_board()[tail_y_pos][tail_x_pos + 1];
    
    // Render node at first unoccupied cell found.
    if (cell_up == safe_cell) {
      x_pos = tail_x_pos;
      y_pos = tail_y_pos - 1;
    } else if (cell_down == safe_cell) {
      x_pos = tail_x_pos;
      y_pos = tail_y_pos + 1;
    } else if (cell_right == safe_cell) {
      x_pos = tail_x_pos + 1;
      y_pos = tail_y_pos;
    } else {
      x_pos = tail_x_pos - 1;
      y_pos = tail_y_pos;
    }

    SnakeNode* new_node = new SnakeNode(y_pos, x_pos);

    if (!m_head) {
        m_head = m_tail = new_node;
    } else {
        m_tail->next = new_node;
        new_node->prev = m_tail;
        m_tail = new_node;
    }
    
    board.insert_at(y_pos, x_pos);
    board.update_frame();
}
