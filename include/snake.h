#ifndef SNAKE_H
#define SNAKE_H

// Represents the snake as a linked list.
// Must have a length.
// The body of the snake is represented by a linked group of nodes.
// Each node stores its own position on the board.
// When the snake's head (root node) moves,
// the rest of the nodes must also follow.
class Snake {
  private:
    int m_length;
    SnakeNode* m_head;
    SnakeNode* m_tail;

  public:
    Snake(int length): m_head(nullptr), m_tail(nullptr) {};
    
    void append(int row, int col) {
      // Using 'new' keyword with a pointer to allocate to the heap.
      // This means we guarantee the object lifetime until we explicitly delete it.
      SnakeNode* new_node = new SnakeNode(row, col);
      if (!m_head) {
        // If there is no head spawned, set new node to both head and tail.
        m_head = m_tail = new_node;
      } else {
        // If there is a head, set tail's next node to the new node.
        // And new node's previous node to the tail.
        // And finally, declare the new node as a the tail.
        m_tail->next = new_node;
        new_node->prev = m_tail;
        tail = new_node;
      }
    }
}

#endif 
