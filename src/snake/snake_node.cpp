#include "snake_node.h"

SnakeNode::SnakeNode(int y_pos, int x_pos)
  : next(nullptr), prev(nullptr),
    m_y_index(y_pos), m_x_index(x_pos),
    m_prev_node_y_index(y_pos), m_prev_node_x_index(x_pos) {}

void SnakeNode::move() {
    m_y_index = m_prev_node_y_index;
    m_x_index = m_prev_node_x_index;
}

