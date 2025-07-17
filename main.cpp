#include <ncurses.h>
#include "objects.h"  // Create a header file instead of directly including .cpp

int main() {
    initscr();
    keypad(stdscr, TRUE); // Enable arrow keys
    noecho();
    curs_set(0);

    int row, col;
    getmaxyx(stdscr, row, col);

    // Display a random asteroid at the start
    ObstacleDisplayer::displayRandomAsteroid(row / 2, col / 2);

    Spaceship spaceship(row - 2, col / 2 -2); // present in objects.cpp
    spaceship.display(); //see objects.cpp

    int c;
    while ((c = getch()) != 'q') { // exit game with q
        switch (c) { //can only move in 1 direction at once
            case KEY_UP:
                spaceship.moveUp();
                break;
            case KEY_DOWN:
                spaceship.moveDown();
                break;
            case KEY_LEFT:
                spaceship.moveLeft();
                break;
            case KEY_RIGHT:
                spaceship.moveRight();
                break;
            case 'r':  // Regenerate random asteroid
                clear();
                ObstacleDisplayer::displayRandomAsteroid(row / 2, col / 2);
                spaceship.display();
                break;
        }
        refresh();
    }

    endwin();
    return 0;
}
