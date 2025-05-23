#include "snake_node.h"

SnakeNode::SnakeNode(int row, int col)
  : next(nullptr), prev(nullptr),
    m_row_index(row), m_col_index(col),
    m_prev_node_row_index(row), m_prev_node_col_index(col) {}

void SnakeNode::move() {
    m_row_index = m_prev_node_row_index;
    m_col_index = m_prev_node_col_index;
}

