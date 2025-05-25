#include "snake.h"
#include "snake_node.h"
#include "board.h"
#include <iostream>

Snake::Snake() : m_head(nullptr), m_tail(nullptr) {}

// Creates the initial head node at the start of the game.
// Takes a reference to the Board type object.
void Snake::spawn(int y_pos, int x_pos, Board* board) {
  SnakeNode* head_node = new SnakeNode(y_pos, x_pos);
  
  m_head = m_tail = head_node; 

  board->insert_at(y_pos, x_pos);
  board->update_frame();
}

// Creates a new node and appends to the end of the snake as the new tail.
// Need to insert the node at the row/col next to the current node.
void Snake::append(Board* board) {
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
    char cell_up    = (tail_y_pos > 0) ? board->get_board()[tail_y_pos - 1][tail_x_pos] : '\0';
    char cell_down  = (tail_y_pos < board->get_height() - 1) ? board->get_board()[tail_y_pos + 1][tail_x_pos] : '\0';
    char cell_left  = (tail_x_pos > 0) ? board->get_board()[tail_y_pos][tail_x_pos - 1] : '\0';
    char cell_right = (tail_x_pos < board->get_width() - 1) ? board->get_board()[tail_y_pos][tail_x_pos + 1] : '\0';
    
    // Render node at first unoccupied cell found.
    // Checks in order of down, right, left, up.
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
      // If there's no head, assign the head and tail to both be the new node.
      // Set head's previous node to be nullptr - it doesn't exist.
        m_head = m_tail = new_node;
        m_head->prev = nullptr;
    } else {
      // Go directly to the tail and set the next node to be the new node.
      // Then, set the prev node of the new node to be the tail.
      // Then, re-assign the tail to the new node.
      // Finally, set tail's next node to be nullptr - it doesn't exist.
        m_tail->next = new_node;
        new_node->prev = m_tail;
        m_tail = new_node;
        m_tail->next = nullptr;
    }
    
    board->insert_at(y_pos, x_pos);
    board->update_frame();
}

// Moving the snake - pseudocode:
// For each node, 
// Set prev co-ordinates to the current co-ordinates,
// Then, set current co-cordinates to the new co-ordinates.
// Then, insert '#' at node's new co-ordinates.
// Finally, insert '~' at node's previous co-ordinates.
// ^ This ensures the snake doesn't leave behind stray '#' chars.

// Moves the snake towards the targeted position on the board.
// Recursively moves each individual node in the list.
void Snake::move(int new_y_pos, int new_x_pos, Board* board) {
  SnakeNode* current = m_head;

  // Capture the node's old position.
  int prev_y = current->get_y_index();
  int prev_x = current->get_x_index();

  // Set previous position to the old position.
  // Set current position to the new position.
  current->set_prev_y_index(prev_y);
  current->set_prev_x_index(prev_x);
  current->set_y_index(new_y_pos);
  current->set_x_index(new_x_pos);

  // Update the frame for the head node.
  board->insert_at(new_y_pos, new_x_pos);
  board->delete_at(prev_y, prev_x);

  // Move to next node.
  current = current->next;

  while (current) {
    int curr_y = current->get_y_index();
    int curr_x = current->get_x_index();

    current->set_prev_y_index(curr_y);
    current->set_prev_x_index(curr_x);

    // Move this node to the previous node's old position.
    current->set_y_index(prev_y);
    current->set_x_index(prev_x);

    board->insert_at(prev_y, prev_x);
    board->delete_at(curr_y, curr_x);

    // Update prev position for the next node to use.
    prev_y = curr_y;
    prev_x = curr_x;

    current = current->next;
  }

  board->update_frame();
}
