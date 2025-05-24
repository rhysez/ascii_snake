
#ifndef SNAKE_NODE_H
#define SNAKE_NODE_H

class SnakeNode {
  private:
    int m_prev_node_y_index;
    int m_prev_node_x_index;

    int m_y_index;
    int m_x_index;

  public:
    SnakeNode(int y_pos, int x_pos);

    SnakeNode* next;
    SnakeNode* prev;

    void set_next(SnakeNode* node) {
      next = node;
    }

    void set_prev(SnakeNode* node) {
      prev = node;
    }

    int get_y_index() const {
      return m_y_index;
    }

    int get_x_index() const {
      return m_x_index;
    }

    void move();
};

#endif

