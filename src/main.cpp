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

int start_game_runtime(Snake* snake, Board* board) {
    while (true) {
        if (kbhit()) {
            char ch = getchar();
            SnakeNode* head = snake->get_head();
            int head_y_pos = head->get_y_index();
            int head_x_pos = head->get_x_index();
            char incoming_cell;
            
            // TODO: Too much duplicated logic. Should encapsulate in function.
            switch (ch) {
              case 'a':
                incoming_cell = board->get_board()[head_y_pos][head_x_pos - 1];
                if (incoming_cell == '#') {
                  std::cout << "You collided with your own body! GAME OVER." << "\n";
                  setNonCanonicalMode(false);
                  std::exit(0);
                }

                snake->move(head_y_pos, head_x_pos - 1, board);
                return 0;
              case 'd':
                incoming_cell = board->get_board()[head_y_pos][head_x_pos + 1];
                if (incoming_cell == '#') {
                  std::cout << "You collided with your own body! GAME OVER." << "\n";
                  setNonCanonicalMode(false);
                  std::exit(0);
                }

                snake->move(head_y_pos, head_x_pos + 1, board);
                return 0;
              case 'w':
                incoming_cell = board->get_board()[head_y_pos - 1][head_x_pos];
                if (incoming_cell == '#') {
                  std::cout << "You collided with your own body! GAME OVER." << "\n";
                  setNonCanonicalMode(false);
                  std::exit(0);
                }
                snake->move(head_y_pos - 1, head_x_pos, board);
                return 0;
              case 's':
                incoming_cell = board->get_board()[head_y_pos + 1][head_x_pos];
                if (incoming_cell == '#') {
                  std::cout << "You collided with your own body! GAME OVER." << "\n";
                  setNonCanonicalMode(false);
                  std::exit(0);
                }
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

    Board board {20, 60};
    Snake snake;

    // Pointers to the board and snake.
    Board* p_board = &board;
    Snake* p_snake = &snake;

    p_snake->spawn(18, 30, p_board);
    
    // Build the initial snake.
    for (int i = 0; i < 5; i++) {
      p_snake->append(p_board);
    } 

    while (true) {
      start_game_runtime(p_snake, p_board);
    } 
    
    setNonCanonicalMode(false);
    return 0;
}

