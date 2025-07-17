#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include "objects.h"

// Spaceship method implementations
Spaceship::Spaceship(int row, int col) : row(row), col(col) {}

void Spaceship::display() {
    mvprintw(row-1, col+1, "^");
    mvprintw(row, col, "/|\\");
    mvprintw(row+1, col-1, "/_^_\\");
    refresh();
}

void Spaceship::moveUp() {
    if (row > 0) {
        row--;
        clear();
        display();
    }
}

void Spaceship::moveDown() {
    int maxRows, maxCols;
    getmaxyx(stdscr, maxRows, maxCols);
    if (row < maxRows - 1) {
        row++;
        clear();
        display();
    }
}

void Spaceship::moveLeft() {
    if (col > 1) {
        col -= 2;
        clear();
        display();
    }
}

void Spaceship::moveRight() {
    int maxRows, maxCols;
    getmaxyx(stdscr, maxRows, maxCols);
    if (col < maxCols - 3) {
        col += 2;
        clear();
        display();
    }
}

void Spaceship::moveDiagonal(int dRow, int dCol) {
    int maxRows, maxCols;
    getmaxyx(stdscr, maxRows, maxCols);
    int newRow = row + dRow;
    int newCol = col + dCol;
    if (newRow >= 0 && newRow < maxRows && newCol >= 0 && newCol < maxCols - 2) {
        row = newRow;
        col = newCol;
        clear();
        display();
    }
}

// Asteroid method implementations
Asteroid::Asteroid(int row, int col, Variation var) : row(row), col(col) {
    switch (var) {
        case VAR1:
            shape = {
                " ____ ",
                "/ o  \\",
                "|  0 |",
                "\\____/"
            };
            break;
        case VAR2:
            shape = {
                " _____ ",
                "/  o  \\",
                "| oo  |",
                "\\_____/"
            };
            break;
        case VAR3:
            shape = {
                " _____ ",
                "/    o\\",
                "| o o |",
                "\\_____/"
            };
            break;
    }
}

void Asteroid::display() const {
    for (size_t i = 0; i < shape.size(); ++i) {
        mvprintw(row + i, col, "%s", shape[i].c_str());
    }
    refresh();
}

const std::vector<std::string>& Asteroid::getShape() const { 
    return shape; 
}

// AsteroidBig method implementations
AsteroidBig::AsteroidBig(int row, int col, Variation var) : row(row), col(col) {
    switch (var) {
        case VAR1:
            shape = {
                " _______",
                "/       \\",
                "|  o  o |",
                "| 0  0  |",
                "\\_______/"
            };
            break;
        case VAR2:
            shape = {
                " _______",
                "/  o    \\",
                "|   0   |",
                "| o  0  |",
                "\\_______/"
            };
            break;
        case VAR3:
            shape = {
                " _______",
                "/  0    \\",
                "|   o   |",
                "|  o  0 |",
                "\\_______/"
            };
            break;
    }
}

void AsteroidBig::display() {
    for (size_t i = 0; i < shape.size(); ++i) {
        mvprintw(row + i, col, "%s", shape[i].c_str());
    }
    refresh();
}

// AsteroidSmall method implementations
AsteroidSmall::AsteroidSmall(int row, int col, Variation var) : row(row), col(col) {
    switch (var) {
        case VAR1:
            shape = {
                " __",
                "/  \\",
                "\\__/"
            };
            break;
        case VAR2:
            shape = {
                " __",
                "/o \\",
                "\\__/"
            };
            break;
        case VAR3:
            shape = {
                " __",
                "/ o\\",
                "\\__/"
            };
            break;
    }
}

void AsteroidSmall::display() {
    for (size_t i = 0; i < shape.size(); ++i) {
        mvprintw(row + i, col, "%s", shape[i].c_str());
    }
    refresh();
}

// ObstacleDisplayer method implementations
void ObstacleDisplayer::displayObstacle(const Asteroid& asteroid, int row, int col) {
    const auto& shape = asteroid.getShape();
    for (size_t i = 0; i < shape.size(); ++i) {
        mvprintw(row + i, col, "%s", shape[i].c_str());
    }
    refresh();
}

void ObstacleDisplayer::displayRandomAsteroid(int row, int col) {
    // Seed random number generator only once
    static bool seedInitialized = false;
    if (!seedInitialized) {
        srand(time(nullptr));
        seedInitialized = true;
    }

    // Randomly choose asteroid type
    int asteroidType = rand() % 3;

    switch (asteroidType) {
        case 0: {
            int adjustedCol = col - 3;  
            int adjustedRow = row - 2;  
            Asteroid randomAsteroid(adjustedRow, adjustedCol, 
                static_cast<Asteroid::Variation>(rand() % 3));
            randomAsteroid.display();
            break;
        }
        case 1: {
            int adjustedCol = col - 4;  
            int adjustedRow = row - 2;  
            AsteroidBig randomBigAsteroid(adjustedRow, adjustedCol, 
                static_cast<AsteroidBig::Variation>(rand() % 3));
            randomBigAsteroid.display();
            break;
        }
        case 2: {
            int adjustedCol = col - 2;  
            int adjustedRow = row - 1;  
            AsteroidSmall randomSmallAsteroid(adjustedRow, adjustedCol, 
                static_cast<AsteroidSmall::Variation>(rand() % 3));
            randomSmallAsteroid.display();
            break;
        }
    }
}