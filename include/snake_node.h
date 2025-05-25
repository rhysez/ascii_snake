
#ifndef SNAKE_NODE_H
#define SNAKE_NODE_H

class SnakeNode {
  private:
    int m_prev_y_index;
    int m_prev_x_index;

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

    void set_prev_y_index(int y_pos) {
      m_prev_y_index = y_pos;
    }
    
    void set_prev_x_index(int x_pos) {
      m_prev_x_index = x_pos;
    }

    void set_y_index(int y_pos) {
      m_y_index = y_pos;
    }

    void set_x_index(int x_pos) {
      m_x_index = x_pos;
    }

    int get_prev_y_index() const {
      return m_prev_y_index;
    }

    int get_prev_x_index() const {
      return m_prev_x_index;
    }

    int get_y_index() const {
      return m_y_index;
    }

    int get_x_index() const {
      return m_x_index;
    }
};

#endif

