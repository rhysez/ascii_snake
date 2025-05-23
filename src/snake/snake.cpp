#include "snake.h"
#include "snake_node.h"
#include "board.h"

Snake::Snake() : m_head(nullptr), m_tail(nullptr) {}

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
