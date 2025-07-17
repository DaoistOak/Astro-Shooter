#include <ncurses.h>
#include "objects.h"  // Create a header file instead of directly including .cpp

int main() {
    initscr();
    keypad(stdscr, TRUE); // Enable arrow keys
    noecho();
    curs_set(0);

    int row, col;
    getmaxyx(stdscr, row, col);

    // Display three Asteroids in a line at the middle of the screen
    int mid_row = row / 2;
    int start_col = col / 2 - 18; // Center the line of asteroids
    Asteroid a1(mid_row, start_col, Asteroid::VAR1);
    Asteroid a2(mid_row, start_col + 12, Asteroid::VAR2);
    Asteroid a3(mid_row, start_col + 24, Asteroid::VAR3);
    a1.display();
    a2.display();
    a3.display();

    // Display three AsteroidBigs in a line below the previous asteroids
    int mid_row_big = mid_row + 5; // Position below the previous asteroids
    AsteroidBig ab1(mid_row_big, start_col, AsteroidBig::VAR1);
    AsteroidBig ab2(mid_row_big, start_col + 12, AsteroidBig::VAR2);
    AsteroidBig ab3(mid_row_big, start_col + 24, AsteroidBig::VAR3);
    ab1.display();
    ab2.display();
    ab3.display();

    // Display three AsteroidSmalls in a line below the previous asteroids
    int mid_row_small = mid_row_big + 5; // Position below the previous asteroids
    AsteroidSmall as1(mid_row_small, start_col, AsteroidSmall::VAR1);
    AsteroidSmall as2(mid_row_small, start_col + 12, AsteroidSmall::VAR2);
    AsteroidSmall as3(mid_row_small, start_col + 24, AsteroidSmall::VAR3);
    as1.display();
    as2.display();
    as3.display();

    Spaceship spaceship(row - 2, col / 2); // present in objects.cpp
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
        }
        refresh();
    }

    endwin();
    return 0;
}
