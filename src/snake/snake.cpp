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
    // If the cell is an invalid byte in memory, replace with null termination character.
    // The null termination character is being used to signify that the cell isn't safe to access.
    char cell_up    = (tail_y_pos > 0) ? board.get_board()[tail_y_pos - 1][tail_x_pos] : '\0';
    char cell_down  = (tail_y_pos < board.get_height() - 1) ? board.get_board()[tail_y_pos + 1][tail_x_pos] : '\0';
    char cell_left  = (tail_x_pos > 0) ? board.get_board()[tail_y_pos][tail_x_pos - 1] : '\0';
    char cell_right = (tail_x_pos < board.get_width() - 1) ? board.get_board()[tail_y_pos][tail_x_pos + 1] : '\0';
    
    // Render node at first unoccupied cell found.
    // Checks in order of down, right, left, up.
    //  BUG: Seems to error when looking off the edge of the board.
    if (cell_down == safe_cell) {
      x_pos = tail_x_pos;
      y_pos = tail_y_pos + 1;
    } else if (cell_right == safe_cell) {
      x_pos = tail_x_pos + 1;
      y_pos = tail_y_pos;
    } else if (cell_left == safe_cell) {
      x_pos = tail_x_pos - 1;
      y_pos = tail_y_pos;
    } else {
      x_pos = tail_x_pos;
      y_pos = tail_y_pos - 1;
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
