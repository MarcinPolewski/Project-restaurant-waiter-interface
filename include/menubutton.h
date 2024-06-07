#pragma once
#include <ncurses.h>
#include <string>

#include "consoleuiobject.h"
#include "waiter.h"
// #include "popuphandler.h"

class PopUpHandler;
class Restaurant;

class MenuButton : public TerminalUIObject
{
protected:
    std::string title;
    bool selected = false;
    PopUpHandler *popUpHandler;

public:
    MenuButton(int height, int width, int yPosition, int xPosition, std::string title, PopUpHandler *popUpHandler, bool selected = false) // not passed by reference due to nature of initialization of buttons
        : TerminalUIObject(height, width, yPosition, xPosition), title(title), selected(selected), popUpHandler(popUpHandler)
    {
        draw();
    }
    void draw() override
    {
        box(window, 0, 0);
        if (selected)
            wattr_on(window, A_REVERSE, nullptr);
        mvwprintw(window, 1, 1, title.c_str());
        wattr_off(window, A_REVERSE, nullptr);

        wrefresh(window);
    }
    void activate()
    {
        selected = true;
    }

    void deactivate()
    {
        selected = false;
    }

    virtual void pressed() = 0;
};

class CloseButton : public MenuButton
{
public:
    CloseButton(int height, int width, int yPosition, int xPosition, PopUpHandler *popUpHandler, bool selected = false)
        : MenuButton(height, width, yPosition, xPosition, std::string("Close"), popUpHandler, selected)
    {
    }

    void pressed() override;
};

class NewLocalOrderButton : public MenuButton
{
    Restaurant *restaurant;
    Table *table;

public:
    NewLocalOrderButton(int height, int width, int yPosition, int xPosition, PopUpHandler *popUpHandler, Restaurant *restaurant, Table *table, bool selected = false)
        : MenuButton(height, width, yPosition, xPosition, std::string("Crete new Local Order"), popUpHandler, selected), restaurant(restaurant), table(table)
    {
    }

    void pressed() override;
};

class ChangeWaiterButton : public MenuButton
{
    Waiter *waiter;
    Restaurant *restaurant;

public:
    ChangeWaiterButton(int height, int width, int yPosition, int xPosition, PopUpHandler *popUpHandler, Restaurant *restaurant, Waiter *waiter, bool selected = false)
        : MenuButton(height, width, yPosition, xPosition, waiter->toString(), popUpHandler, selected), waiter(waiter), restaurant(restaurant)
    {
    }

    void pressed() override;
};