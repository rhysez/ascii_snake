#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include "board.h"
#include "snake.h"

// Activates non canonical mode.
// Instead of waiting for enter,
// user input will be read on each key press.
// Uses oldt to store old terminal settings to restore after non canonical mode.
void setNonCanonicalMode(bool enable) {
    static struct termios oldt, newt;
    if (enable) {
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);         
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);  
    } else {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt); 
    }
}

// Logic for detecting a key press - non blocking.
int kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

void free_mem(Board* board, Snake* snake) {
  delete board;
  delete snake;
}

int assess_incoming_cell(Board* board, Snake* snake, int y, int x) {
  if (y < 0 || y >= board->get_height() || x < 0 || x >= board->get_width()) {
    return 1;
  }

  char incoming_cell = board->get_board()[y][x];
  if (incoming_cell == '#') {
    std::cout << "You collided with your own body! GAME OVER." << "\n";
    setNonCanonicalMode(false);
    std::exit(0);
    return 2;
  }

  if (incoming_cell == 'O') {
    board->increment_score();
    board->spawn_fruit();
    snake->append(board);
  }
  return 0;
}

// Responsible for running the game and executing moves.
int run_session(Snake* snake, Board* board) {
    while (true) {
        if (kbhit()) {
            char ch = getchar();
            SnakeNode* head = snake->get_head();
            int head_y_pos = head->get_y_index();
            int head_x_pos = head->get_x_index();

            int result;
            
            switch (ch) {
              case 'a':
                result = assess_incoming_cell(board, snake, head_y_pos, head_x_pos - 1);
                if (result == 0) {
                  snake->move(head_y_pos, head_x_pos - 1, board);
                }
                return 0;
              case 'd':
                result = assess_incoming_cell(board, snake, head_y_pos, head_x_pos + 1);
                if (result == 0) {
                  snake->move(head_y_pos, head_x_pos + 1, board);
                }
                return 0;
              case 'w':
                result = assess_incoming_cell(board, snake, head_y_pos - 1, head_x_pos);
                if (result == 0) {
                  snake->move(head_y_pos - 1, head_x_pos, board);
                } 
                return 0;
              case 's':
                result = assess_incoming_cell(board, snake, head_y_pos + 1, head_x_pos);
                if (result == 0) {
                  snake->move(head_y_pos + 1, head_x_pos, board);
                }
                return 0;
              case 'x':
                setNonCanonicalMode(false);
                std::exit(0);
              default:
                std::cout << "No binding available for this key" << "\n";
                return 1;
            }
        }
    }
}

int main() {
    setNonCanonicalMode(true);
    const int INITIAL_SNAKE_SIZE = 5;

    Board board {16, 46};
    Snake snake;

    // Pointers to the board and snake.
    Board* p_board = &board;
    Snake* p_snake = &snake;

    int spawn_y = p_board->get_board().size() / 2;
    int spawn_x = p_board->get_board()[0].size() / 2;

    p_snake->spawn(spawn_y, spawn_x, p_board);
    p_board->spawn_fruit();
    
    // Build the initial snake.
    for (int i = 0; i < INITIAL_SNAKE_SIZE; i++) {
      p_snake->append(p_board);
    } 

    while (true) {
      run_session(p_snake, p_board);
    } 
    
    setNonCanonicalMode(false);
    return 0;
}

