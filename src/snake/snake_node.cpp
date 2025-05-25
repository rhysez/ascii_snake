#include "snake_node.h"

SnakeNode::SnakeNode(int y_pos, int x_pos)
  : next(nullptr), prev(nullptr),
    m_y_index(y_pos), m_x_index(x_pos),
    m_prev_y_index(y_pos), m_prev_x_index(x_pos) {}
