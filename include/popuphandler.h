#pragma once

#include <ncurses.h>
#include <stdexcept>
#include <stack>

// #include "restaurant.h"
class Restaurant;
class PopUpMenu;
class TablePopUpMenu;
class ChangeWaiterPopUpMenu;
class LocalOrdersPopUpMenu;
class UITable;

class PopUpHandler
{
    WINDOW *backgroundWindow;
    Restaurant *restaurant;
    std::stack<PopUpMenu *> windowStack;

    // ========= pointers to popUps
    std::unique_ptr<TablePopUpMenu> tablePopUpMenu;
    std::unique_ptr<ChangeWaiterPopUpMenu> changeWaiterPopUpMenu;
    std::unique_ptr<LocalOrdersPopUpMenu> localOrdersPopUpMenu;

public:
    PopUpHandler(WINDOW *background, Restaurant *restaurant);

    TablePopUpMenu *newTablePopUpMenu(UITable &table);
    ChangeWaiterPopUpMenu *newChangeWaiterPopUpMenu();
    LocalOrdersPopUpMenu *newLocalOrdersPopUpMenu();

    bool closePopUpMenu();

    void moveUp();
    void moveDown();
    bool buttonPressed();

    void draw();
};