#pragma once

#include <ncurses.h>
#include <vector>
#include <cstring>

#include "consoleuiobject.h"
#include "popuphandler.h"
#include "menubutton.h"
#include "uitable.h"
#include "menu.h"

class PopUpMenu : public TerminalUIObject
{
    /*
        Structure:
            - scroll menu with buttons
            - other buttons
    */
protected:
    std::vector<std::unique_ptr<MenuButton>> scrollableButtons; // butons that make scrollable view
    std::vector<std::unique_ptr<MenuButton>> staticButtons;     // other buttons in Menu

    int scrollStartY;
    std::vector<std::unique_ptr<MenuButton>>::iterator firstDisplayedScrollButton;
    std::vector<std::unique_ptr<MenuButton>>::iterator selectedButton;

    PopUpHandler *popUpHandler;

    void auto_initialize()
    {
        if (!scrollableButtons.empty())
        {
            firstDisplayedScrollButton = scrollableButtons.begin();
            selectedButton = scrollableButtons.begin();
            (*selectedButton)->activate();
        }
        else if (!staticButtons.empty())
        {
            selectedButton = staticButtons.begin();
            (*selectedButton)->activate();
        }
        else
            throw std::invalid_argument("cannot initialize pop up menu, that has no buttons(scrollable or static)");
    }

public:
    // CONSTRUCTOR MUST INITIALIZED ITERATORS !!!!!

    PopUpMenu(int height, int width, int yPosition, int xPosition, PopUpHandler *popUpHandler)
        : TerminalUIObject(height, width, yPosition, xPosition), popUpHandler(popUpHandler)
    {
    }

    // this constructor turned out ugly, because it's the only way to call another constructor
    PopUpMenu(WINDOW *background, PopUpHandler *popUpHandler, int height = 40, int width = 60)
        : PopUpMenu(height, width,
                    getbegy(background) + ((getmaxy(background) - height) / 2),
                    getbegx(background) + ((getmaxx(background) - width) / 2),
                    popUpHandler)
    {
    }

    void drawStaticButtons()
    {
        for (auto &it : staticButtons)
        {
            it->draw();
        }
    }
    void drawScrollabeButtons()
    {
        int buttonY = scrollStartY;
        int cnt = 0;
        for (auto it = firstDisplayedScrollButton; cnt != NUMBER_OF_BUTTONS_IN_SCROLL && it != scrollableButtons.end(); ++cnt, ++it)
        {
            (*it)->setNewY(buttonY); // reposition buttons
            (*it)->draw();           // draw button
            buttonY += BUTTON_HEIGHT;
        }
    }

    void draw() override
    {
        box(window, 0, 0);
        // write text here ??
        wrefresh(window);
        drawScrollabeButtons();
        drawStaticButtons();
    }

    void moveUp()
    {
        (*selectedButton)->deactivate();
        if (selectedButton != scrollableButtons.begin())
        {
            if (selectedButton != staticButtons.begin())
            {
                if (selectedButton == firstDisplayedScrollButton)
                {
                    --firstDisplayedScrollButton;
                }
                --selectedButton;
                // reposition buttons in scroll view if neccessary
            }
            else // selectedButton == staticButtons.begin()
            {
                if (scrollableButtons.empty())
                {
                    selectedButton = staticButtons.end() - 1;
                }
                else
                {
                    selectedButton = scrollableButtons.end() - 1;
                    firstDisplayedScrollButton = selectedButton - (NUMBER_OF_BUTTONS_IN_SCROLL - 1);
                }
            }
        }
        else // selectedButton == scrollableButtons.begin() -> cursor is in scroll
        {
            if (staticButtons.empty())
            {
                selectedButton = scrollableButtons.end() - 1;
                firstDisplayedScrollButton = selectedButton - (NUMBER_OF_BUTTONS_IN_SCROLL - 1);
            }
            else
            {
                selectedButton = staticButtons.end() - 1;
            }
        }
        (*selectedButton)->activate();
    }

    void moveDown()
    {
        (*selectedButton)->deactivate();
        if (selectedButton != scrollableButtons.end() - 1)
        {
            if (selectedButton != staticButtons.end() - 1)
            {
                if (selectedButton == firstDisplayedScrollButton + (NUMBER_OF_BUTTONS_IN_SCROLL - 1))
                    ++firstDisplayedScrollButton;
                ++selectedButton;
            }
            else // selectedButton == staticButtons.end() -1
            {
                if (scrollableButtons.empty())
                {
                    selectedButton = staticButtons.begin();
                }
                else
                {
                    selectedButton = scrollableButtons.begin();
                    firstDisplayedScrollButton = selectedButton;
                }
            }
        }
        else // selectedButton == scrollableButtons.end() -1 -> cursor is in scroll
        {
            if (staticButtons.empty())
            {
                selectedButton = scrollableButtons.begin();
                firstDisplayedScrollButton = selectedButton;
            }
            else
            {
                selectedButton = staticButtons.begin();
            }
        }
        (*selectedButton)->activate();
    }

    void buttonPressed()
    {
        (*selectedButton)->pressed();
    }
};

class MenuPopUpMenu : public PopUpMenu
{
    const Menu &menu;

public:
    MenuPopUpMenu(WINDOW *background, PopUpHandler *popUpHandler, Menu const &menu, int height = 40, int width = 60);
};

class ErrorPrompt : public PopUpMenu // used when error occurs, to signal it to user
{
public:
    ErrorPrompt(WINDOW *background, PopUpHandler *popUpHandler, std::string message, int height = 5, int width = 60);
};

class ChangeWaiterPopUpMenu : public PopUpMenu // used to select new waiter
{
    Restaurant *restaurant;

public:
    ChangeWaiterPopUpMenu(WINDOW *background, PopUpHandler *popUpHandler, Restaurant *rest, int height = 40, int width = 60);
};

class NoOrderAssignedToTablePopUpMenu : public PopUpMenu // used to signal to user, that this table does not have a order assigned
{
    Restaurant *restaurant;
    Table *table;

public:
    NoOrderAssignedToTablePopUpMenu(WINDOW *background, PopUpHandler *popUpHandler, Restaurant *rest, Table *table, int height = 9, int width = strlen(NO_ORDER_ASSIGNED_MESS) + 2);
};

class LocalOrderPopUpMenu : public PopUpMenu
{
    Restaurant *restaurant;
    Order *order;

public:
    LocalOrderPopUpMenu(WINDOW *background, PopUpHandler *popUpHandler, Restaurant *rest, Order *order, int height = 40, int width = 60);
};

class LocalOrdersPopUpMenu : public PopUpMenu // presents all local order
{
    Restaurant *restaurant;

public:
    LocalOrdersPopUpMenu(WINDOW *background, PopUpHandler *popUpHandler, Restaurant *restaurant, int height = 40, int width = 60);
};

class RemoteOrdersPopUpMenu : public PopUpMenu
{
    Restaurant *restaurant;

public:
    RemoteOrdersPopUpMenu(WINDOW *background, PopUpHandler *popUpHandler, Restaurant *restaurant, int height = 40, int width = 60);
};
