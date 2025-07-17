#ifndef OBJECTS_H
#define OBJECTS_H

#include <vector>
#include <string>

class Spaceship {
public:
    Spaceship(int row, int col);
    void display();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void moveDiagonal(int dRow, int dCol);

private:
    int row;
    int col;
};

class Asteroid {
public:
    enum Variation {
        VAR1 = 0,
        VAR2 = 1,
        VAR3 = 2
    };

    Asteroid(int row, int col, Variation var = VAR1);
    void display() const;
    const std::vector<std::string>& getShape() const;

private:
    int row;
    int col;
    std::vector<std::string> shape;
};

class AsteroidBig {
public:
    enum Variation {
        VAR1 = 0,
        VAR2 = 1,
        VAR3 = 2
    };

    AsteroidBig(int row, int col, Variation var = VAR1);
    void display();

private:
    int row;
    int col;
    std::vector<std::string> shape;
};

class AsteroidSmall {
public:
    enum Variation {
        VAR1 = 0,
        VAR2 = 1,
        VAR3 = 2
    };

    AsteroidSmall(int row, int col, Variation var = VAR1);
    void display();

private:
    int row;
    int col;
    std::vector<std::string> shape;
};

class ObstacleDisplayer {
public:
    static void displayObstacle(const Asteroid& asteroid, int row, int col);
    
    // New function to display a random asteroid
    static void displayRandomAsteroid(int row, int col);
};

#endif // OBJECTS_H 