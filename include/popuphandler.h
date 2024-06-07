#pragma once

#include <ncurses.h>
#include <stdexcept>
#include <stack>
#include <algorithm>

// #include "restaurant.h"
class Restaurant;
class PopUpMenu;
class TablePopUpMenu;
class ChangeWaiterPopUpMenu;
class LocalOrdersPopUpMenu;
class RemoteOrdersPopUpMenu;
class ErrorPrompt;
class UITable;

class PopUpHandler
{
    WINDOW *backgroundWindow;
    Restaurant *restaurant;
    std::stack<std::unique_ptr<PopUpMenu>> windowStack;

    // ========= pointers to popUps
    // std::unique_ptr<TablePopUpMenu> tablePopUpMenu;
    // std::unique_ptr<ChangeWaiterPopUpMenu> changeWaiterPopUpMenu;
    // std::unique_ptr<LocalOrdersPopUpMenu> localOrdersPopUpMenu;
    // std::unique_ptr<RemoteOrdersPopUpMenu> remoteOrdersPopUpMenu;
    // std::unique_ptr<ErrorPrompt> errorPrompt;

public:
    PopUpHandler(WINDOW *background, Restaurant *restaurant);

    void newTablePopUpMenu(UITable &table);
    void newChangeWaiterPopUpMenu();
    void newLocalOrdersPopUpMenu();
    void newRemoteOrdersPopUpMenu();
    void newErrorPrompt(std::string message);

    bool closePopUpMenu();

    void moveUp();
    void moveDown();
    bool buttonPressed();

    void draw();
};