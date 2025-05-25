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

int main() {
    setNonCanonicalMode(true);

    Board board {20, 60};
    Snake snake;

    // Pointer to the board.
    // Allows Snake methods to access Board from within members.
    Board* p_board = &board;

    snake.spawn(18, 30, p_board);

    while (true) {
        if (kbhit()) {
            char ch = getchar();
            snake.append(p_board);
        }
    }

    setNonCanonicalMode(false);
    return 0;
}

