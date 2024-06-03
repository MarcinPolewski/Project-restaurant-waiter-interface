#pragma once

#include <ncurses.h>
#include <stdexcept>
#include <stack>

// #include "restaurant.h"
class Restaurant;

#include "popupmenu.h"

class PopUpHandler
{
    WINDOW *backgroundWindow;
    Restaurant *restaurant;
    std::stack<PopUpMenu *> windowStack;

    // ========= pointers to popUps
    std::unique_ptr<TablePopUpMenu> tablePopUpMenu;

public:
    PopUpHandler(WINDOW *background, Restaurant *restaurant)
        : backgroundWindow(background), restaurant(restaurant)
    {
    }

    TablePopUpMenu *newTablePopUpMenu(UITable &table)
    {
        tablePopUpMenu.reset(new TablePopUpMenu(backgroundWindow, this, table));
        windowStack.push(tablePopUpMenu.get());
        return tablePopUpMenu.get();
    }

    bool closePopUpMenu()
    {
        if (windowStack.size() == 1)
        {
            windowStack.pop();
            tablePopUpMenu.reset();
            return true;
        }
        else
        {
            PopUpMenu *windowToDelete = windowStack.top();
            windowStack.pop();

            if (dynamic_cast<TablePopUpMenu *>(windowToDelete))
                tablePopUpMenu.reset();
        }
        return false;
    }

    void moveUp()
    {
        if (windowStack.empty())
            throw std::invalid_argument("no popup is displayed");
        windowStack.top()->moveUp();
    }

    void moveDown()
    {
        if (windowStack.empty())
            throw std::invalid_argument("no popup is displayed");
        windowStack.top()->moveDown();
    }

    void draw()
    {
        if (!windowStack.empty())
            windowStack.top()->draw();
    }

    bool buttonPressed()
    {
        if (windowStack.empty())
            throw std::invalid_argument("no popup is displayed");
        windowStack.top()->buttonPressed();

        // figure out which menu it is
        // get input

        if (windowStack.empty())
            return true;
        return false;
        // gdybysmy tutaj mieli to, co zostalo wcisniete, to
        // mozna duzo z tym zrobic, wywolac nowe okno co cos zwraca
        // mozna porobic dynamic casty, zeby wiedziec jakie to menu i jakie ma guziki
        // how to interact with mainLoop ??
        // necessary when closing, switching modes(the same as close)
    }
};