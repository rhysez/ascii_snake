
#ifndef SNAKE_NODE_H
#define SNAKE_NODE_H

class SnakeNode {
  private:
    int m_prev_node_row_index;
    int m_prev_node_col_index;

    int m_row_index;
    int m_col_index;

  public:
    SnakeNode(int row, int col);

    SnakeNode* next;
    SnakeNode* prev;

    void set_next(SnakeNode* node) {
      next = node;
    }

    void set_prev(SnakeNode* node) {
      prev = node;
    }

    int get_row_index() const {
      return m_row_index;
    }

    int get_col_index() const {
      return m_col_index;
    }

    void move();
};

#endif

