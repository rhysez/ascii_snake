#include "snake.h"
#include "snake_node.h"
#include "board.h"

Snake::Snake() : m_head(nullptr), m_tail(nullptr) {}

// Creates the initial head node at the start of the game.
void Snake::spawn(int row, int col, Board& board) {
  SnakeNode* head_node = new SnakeNode(row, col);
  board.insert_at(row, col);

  m_head = m_tail = head_node; 
}

// Creates a new node and appends to the end of the snake as the new tail.
// Adds a '#' to the relevant co-ordinate on the board.
// Takes a reference to the board.
void Snake::append(int row, int col, Board& board) {
    SnakeNode* new_node = new SnakeNode(row, col);
    board.insert_at(row, col);

    if (!m_head) {
        m_head = m_tail = new_node;
    } else {
        m_tail->next = new_node;
        new_node->prev = m_tail;
        m_tail = new_node;
    }
}
