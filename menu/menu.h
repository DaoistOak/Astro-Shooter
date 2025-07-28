#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>
#include <ncurses.h>
#include "../objects/objects.h"

class MenuButton {
public:
    MenuButton(int row, int col, const std::string& label);
    void display(bool selected = false) const;
    int getRow() const;
    int getCol() const;
    const std::string& getLabel() const;
private:
    int row;
    int col;
    std::string label;
};

class MenuBox {
public:
    MenuBox(int row, int col, int width, int height, const std::string& title);
    void display() const;
    int getRow() const;
    int getCol() const;
private:
    int row;
    int col;
    int width;
    int height;
    std::string title;
};

class Menu {
public:
    Menu(int row, int col, int width, int height, const std::string& title);
    void addButton(const std::string& label);
    int run(); // returns the index of the selected button
private:
    MenuBox box;
    std::vector<MenuButton> buttons;
    int selectedIndex;
};

#endif // MENU_H 