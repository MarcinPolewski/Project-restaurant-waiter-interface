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
    const unsigned int numberOfScrollButtonsOnScreen;

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

    PopUpMenu(int height, int width, int yPosition, int xPosition, PopUpHandler *popUpHandler, unsigned int numberOfScrollButtons = NUMBER_OF_BUTTONS_IN_SCROLL)
        : TerminalUIObject(height, width, yPosition, xPosition), popUpHandler(popUpHandler), numberOfScrollButtonsOnScreen(numberOfScrollButtons)
    {
    }

    // this constructor turned out ugly, because it's the only way to call another constructor
    PopUpMenu(WINDOW *background, PopUpHandler *popUpHandler, int height = 40, int width = 60, unsigned int numberOfScrollButtons = NUMBER_OF_BUTTONS_IN_SCROLL)
        : PopUpMenu(height, width,
                    getbegy(background) + ((getmaxy(background) - height) / 2),
                    getbegx(background) + ((getmaxx(background) - width) / 2),
                    popUpHandler,
                    numberOfScrollButtons)
    {
    }

    virtual void drawInformation() {}

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
        unsigned int cnt = 0;
        for (auto it = firstDisplayedScrollButton; cnt != numberOfScrollButtonsOnScreen && it != scrollableButtons.end(); ++cnt, ++it)
        {
            (*it)->setNewY(buttonY); // reposition buttons
            (*it)->draw();           // draw button
            buttonY += BUTTON_HEIGHT;
        }
    }

    virtual void update() {}

    void draw() override
    {
        box(window, 0, 0);
        // write text here ??
        drawInformation();
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
                    int firstDisplayedOffset = std::min((size_t)numberOfScrollButtonsOnScreen, scrollableButtons.size()) - 1;
                    firstDisplayedScrollButton = selectedButton - firstDisplayedOffset;
                }
            }
        }
        else // selectedButton == scrollableButtons.begin() -> cursor is in scroll
        {

            if (staticButtons.empty())
            {
                selectedButton = scrollableButtons.end() - 1;
                int firstDisplayedOffset = std::min((size_t)numberOfScrollButtonsOnScreen, scrollableButtons.size()) - 1;
                firstDisplayedScrollButton = selectedButton - firstDisplayedOffset;
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
                if (selectedButton == firstDisplayedScrollButton + (numberOfScrollButtonsOnScreen - 1))
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

    virtual void buttonPressed()
    {
        (*selectedButton)->pressed();
    }
};

class MenuPopUpMenu : public PopUpMenu
{
    const Menu &menu;

public:
    MenuPopUpMenu(WINDOW *background, PopUpHandler *popUpHandler, Menu const &menu);
    void drawInformation() override;
};

class ErrorPrompt : public PopUpMenu // used when error occurs, to signal it to user
{
    std::string message;

public:
    ErrorPrompt(WINDOW *background, PopUpHandler *popUpHandler, std::string message);

    void drawInformation() override;
};

class ChangeWaiterPopUpMenu : public PopUpMenu // used to select new waiter
{
    UIRestaurant *restaurant;

public:
    ChangeWaiterPopUpMenu(WINDOW *background, PopUpHandler *popUpHandler, UIRestaurant *rest);
    void drawInformation() override;
};

class NoOrderAssignedToTablePopUpMenu : public PopUpMenu // used to signal to user, that this table does not have a order assigned
{
    UIRestaurant *restaurant;
    Table *table;

public:
    NoOrderAssignedToTablePopUpMenu(WINDOW *background, PopUpHandler *popUpHandler, UIRestaurant *rest, Table *table);
    void drawInformation() override;
};

class LocalOrderPopUpMenu : public PopUpMenu
{
    UIRestaurant *restaurant;
    LocalOrder *order;

public:
    LocalOrderPopUpMenu(WINDOW *background, PopUpHandler *popUpHandler, UIRestaurant *rest, LocalOrder *order);
    void drawInformation() override;
    void update() override;
    void buttonPressed() override;
};

class LocalOrdersPopUpMenu : public PopUpMenu // presents all local order
{
    UIRestaurant *restaurant;

public:
    LocalOrdersPopUpMenu(WINDOW *background, PopUpHandler *popUpHandler, UIRestaurant *restaurant);
    void drawInformation() override;
    void update() override;
};

class RemoteOrdersPopUpMenu : public PopUpMenu
{
    UIRestaurant *restaurant;

public:
    RemoteOrdersPopUpMenu(WINDOW *background, PopUpHandler *popUpHandler, UIRestaurant *restaurant);
    void drawInformation() override;
};

class AddItemToOrderPopUpMenu : public PopUpMenu
{
    Order *order;
    Menu const &menu;

public:
    AddItemToOrderPopUpMenu(WINDOW *background, PopUpHandler *popUpHandler, Order *order, Menu const &menu);
    void drawInformation() override;
};

class MenuItemView : public PopUpMenu
{
    MenuItem const &menuItem;

public:
    MenuItemView(WINDOW *background, PopUpHandler *popUpHandler, MenuItem const &menuItem);
    void drawInformation() override;
};

class OrderItemView : public PopUpMenu
{
    OrderItem *orderItem;

public:
    OrderItemView(WINDOW *background, PopUpHandler *popUpHandler, OrderItem *orderItem);
    void drawInformation() override;
};

class SetDisciountPopUpMenu : public PopUpMenu
{
    OrderItem *orderItem;

public:
    SetDisciountPopUpMenu(WINDOW *background, PopUpHandler *popUpHandler, OrderItem *orderItem);
};

class SetQuantityPopUpMenu : public PopUpMenu
{
    Order *order;
    MenuItem const &menuItem;

public:
    SetQuantityPopUpMenu(WINDOW *background, PopUpHandler *popUpHandler, Order *order, MenuItem const &menuItem);
    void drawInformation() override;
};
