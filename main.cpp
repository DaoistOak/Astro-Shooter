#include <ncurses.h>
#include "objects/objects.h"
#include "menu/menu.h"

int showMenu(int row, int col) {
    Menu menu(row/2 - 5, col/2 - 10, 20, 7, "Main Menu");
    menu.addButton("Play");
    menu.addButton("Exit");
    return menu.run();
}

int main() {
    initscr();
    keypad(stdscr, TRUE); // Enable arrow keys
    noecho();
    curs_set(0);

    int row, col;
    getmaxyx(stdscr, row, col);

    // Create and show menu
    int choice = showMenu(row, col);
    if (choice == 1) { // Exit
        endwin();
        return 0;
    }
    clear();

    ObstacleDisplayer::displayRandomAsteroid(row / 2, col / 2);

    Spaceship spaceship(row - 2, col / 2 -2); // present in objects.cpp
    spaceship.display(); //see objects.cpp

    int c;
    while (true) {
        c = getch();
        if (c == 'q') {
            // Open the menu again
            clear();
            int choice = showMenu(row, col);
            if (choice == 1) { // Exit
                endwin();
                return 0;
            }
            clear();
            ObstacleDisplayer::displayRandomAsteroid(row / 2, col / 2);
            spaceship.display();
            continue;
        }
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
            case 'r':
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
