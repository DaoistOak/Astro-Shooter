#include "menu.h"
#include <ncurses.h>
#include "../objects/objects.h"

MenuButton::MenuButton(int row, int col, const std::string& label)
    : row(row), col(col), label(label) {}

void MenuButton::display(bool selected) const {
    if (selected) {
        attron(A_REVERSE);
    }
    mvprintw(row, col, "%s", label.c_str());
    if (selected) {
        attroff(A_REVERSE);
    }
}

int MenuButton::getRow() const { return row; }
int MenuButton::getCol() const { return col; }
const std::string& MenuButton::getLabel() const { return label; }

MenuBox::MenuBox(int row, int col, int width, int height, const std::string& title)
    : row(row), col(col), width(width), height(height), title(title) {}

void MenuBox::display() const {
    // Draw box using ncurses
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (i == 0 || i == height - 1) {
                mvaddch(row + i, col + j, '-');
            } else if (j == 0 || j == width - 1) {
                mvaddch(row + i, col + j, '|');
            }
        }
    }
    // Draw corners
    mvaddch(row, col, '+');
    mvaddch(row, col + width - 1, '+');
    mvaddch(row + height - 1, col, '+');
    mvaddch(row + height - 1, col + width - 1, '+');
    // Draw title
    mvprintw(row, col + 2, "%s", (" " + title + " ").c_str());
}

Menu::Menu(int row, int col, int width, int height, const std::string& title)
    : box(row, col, width, height, title), selectedIndex(0) {}

void Menu::addButton(const std::string& label) {
    int btnRow = box.getRow() + 2 + buttons.size();
    int btnCol = box.getCol() + 2;
    buttons.emplace_back(btnRow, btnCol, label);
}

int Menu::run() {
    int ch;
    while (true) {
        clear();
        box.display();
        for (size_t i = 0; i < buttons.size(); ++i) {
            buttons[i].display(i == selectedIndex);
        }
        refresh();
        ch = getch();
        switch (ch) {
            case KEY_UP:
                if (selectedIndex > 0) selectedIndex--;
                break;
            case KEY_DOWN:
                if (selectedIndex < (int)buttons.size() - 1) selectedIndex++;
                break;
            case '\n':
            case KEY_ENTER:
                return selectedIndex;
        }
    }
}

// Helper getters for MenuBox
int MenuBox::getRow() const { return row; }
int MenuBox::getCol() const { return col; } 