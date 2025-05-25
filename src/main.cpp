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

// TODO: This should also handle eating a fruit when incoming_cell is a fruit.
void assess_incoming_cell(Board* board, int y, int x) {
  char incoming_cell = board->get_board()[y][x];
  if (incoming_cell == '#') {
    std::cout << "You collided with your own body! GAME OVER." << "\n";
    setNonCanonicalMode(false);
    std::exit(0);  
  }
}

// Responsible for running the game and executing moves.
int run_session(Snake* snake, Board* board) {
    while (true) {
        if (kbhit()) {
            char ch = getchar();
            SnakeNode* head = snake->get_head();
            int head_y_pos = head->get_y_index();
            int head_x_pos = head->get_x_index();
            
            switch (ch) {
              case 'a':
                assess_incoming_cell(board, head_y_pos, head_x_pos - 1);
                snake->move(head_y_pos, head_x_pos - 1, board);
                return 0;
              case 'd':
                assess_incoming_cell(board, head_y_pos, head_x_pos + 1);
                snake->move(head_y_pos, head_x_pos + 1, board);
                return 0;
              case 'w':
                assess_incoming_cell(board, head_y_pos - 1, head_x_pos);
                snake->move(head_y_pos - 1, head_x_pos, board);
                return 0;
              case 's':
                assess_incoming_cell(board, head_y_pos + 1, head_x_pos);
                snake->move(head_y_pos + 1, head_x_pos, board);
                return 0;
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

    Board board {20, 60};
    Snake snake;

    // Pointers to the board and snake.
    Board* p_board = &board;
    Snake* p_snake = &snake;

    p_snake->spawn(18, 30, p_board);
    
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

