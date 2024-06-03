#pragma once

#include <ncurses.h>
#include <stdexcept>
#include <stack>

// #include "restaurant.h"
class Restaurant;
class PopUpMenu;
class TablePopUpMenu;
class UITable;

class PopUpHandler
{
    WINDOW *backgroundWindow;
    Restaurant *restaurant;
    std::stack<PopUpMenu *> windowStack;

    // ========= pointers to popUps
    std::unique_ptr<TablePopUpMenu> tablePopUpMenu;

public:
    PopUpHandler(WINDOW *background, Restaurant *restaurant);

    TablePopUpMenu *newTablePopUpMenu(UITable &table);

    bool closePopUpMenu();

    void moveUp();
    void moveDown();
    bool buttonPressed();

    void draw();
};