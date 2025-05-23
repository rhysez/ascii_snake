#ifndef SNAKE_H
#define SNAKE_H

#include "snake_node.h"
#include "board.h"

// Represents the snake as a linked list.
// Must have a length.
// The body of the snake is represented by a linked group of nodes.
// Each node stores its own position on the board.
// When the snake's head (root node) moves,
// the rest of the nodes must also follow.

// The nodes of the snake are ordered from head to tail.
// I.E the 'next' node will move towards the tail,
// And the 'prev' node will move back towards the head.
class Snake {
  private:
    SnakeNode* m_head;
    SnakeNode* m_tail;

  public:
    Snake();
    
    void append(int row, int col, Board& board); 

    SnakeNode* get_head() const {
      return m_head;
    }

    SnakeNode* get_tail() const {
      return m_tail;
    }
};

#endif 
