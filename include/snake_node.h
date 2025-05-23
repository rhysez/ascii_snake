#ifndef SNAKE_NODE_H
#define SNAKE_NODE_H

// Represents an individual node in the snake's body.
// Stores pointers to the next and previous node in the body (nullptr if no node available).
// Stores the current row and column the node resides in.
// Stores the positions of the previous node (from head to tail) so that it can follow later.
class SnakeNode {
  private:
    SnakeNode* m_next;
    SnakeNode* m_prev;

    int m_prev_node_row_index;
    int m_prev_node_col_index;

    int m_row_index;
    int m_col_index;

  public:
    SnakeNode(int row, int col);

    void set_next(SnakeNode* node) {
      m_next = node;
    }

    void set_prev(SnakeNode* node) {
      m_prev = node;
    }

    SnakeNode* get_next() const {
      return m_next;
    }

    SnakeNode* get_prev() const {
      return m_prev;
    }

    int get_row_index() const {
      return m_row_index;
    }

    int get_col_index() const {
      return m_col_index;
    }

    // Updates the position of the SnakeNode
    // to the old position of the previous node.
    void move() const {
      m_row_index = m_prev_node_row_index;
      m_col_index = m_prev_node_col_index;
    }
}

#endif
