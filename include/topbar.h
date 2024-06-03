#pragma once

#include <ncurses.h>
#include <vector>

#include "consoleuiobject.h"

class PopUpHandler;
class Restaurant;
class Waiter;

class TopBarButton
{
protected:
    std::string name;

public:
    PopUpHandler *popUpHandler;
    TopBarButton(std::string name, PopUpHandler *popUpHandler); // string not passed by reference due to nature of it's use
    // : name(name), popUpHandler(popUpHandler)
    // {
    // }
    virtual std::string toString() { return name; }
    virtual bool pressed() = 0;
    virtual void update() = 0;
    virtual ~TopBarButton() = default;
};

class ChangeWaiterTopBarButton : public TopBarButton
{
    Restaurant *restaurant;

public:
    ChangeWaiterTopBarButton(PopUpHandler *popUpHandler, Restaurant *restaurant);
    //: TopBarButton(std::string("Change Waiter" + currentWaiter->toString()), popUpHandler) {}
    bool pressed();
    void update();
    // {
    //     popUpHandler->newChangeWaiterPopUpMenu();
    //     return true;
    // }
};

// struct RemoteOrderTopBarButton : public TopBarButton
// {

// }

class TopBar : public TerminalUIObject
{
    int selection = 0; // inx to currently pointed button
    std::vector<std::unique_ptr<TopBarButton>> buttons;
    bool active = true;
    PopUpHandler *popUpHandler;
    Restaurant *restaurant;

public:
    TopBar(int height, int width, int positionY, int positionX, PopUpHandler *popUpHandler, Restaurant *restaurant);
    //     : TerminalUIObject(height, width, positionY, positionX), popUpHandler(popUpHandler), restaurant(restaurant)
    // {
    //     buttons.push_back(std::make_unique<ChangeWaiterTopBarButton>(popUpHandler, restaurant->getCurrentWaiter()));
    //     draw();
    // }

    void draw() override;
    void update();
    // {
    //     int width = getmaxx(window);
    //     int widthPerButton = width / buttons.size();

    //     // ============== draw buttons to window
    //     int cursorX = 1;
    //     int cursorY = 1;

    //     for (int i = 0; i < (int)buttons.size(); i++)
    //     {

    //         // calculate button position offset from the left
    //         int offset = (widthPerButton - buttons[i]->name.size()) / 2;

    //         if (active && i == selection) // print menu as selected if neccessary
    //             wattr_on(window, A_REVERSE, nullptr);
    //         mvwprintw(window, cursorY, cursorX + offset, buttons[i]->name.c_str());

    //         wattr_off(window, A_REVERSE, nullptr);
    //         cursorX += widthPerButton;
    //         if (i != (int)buttons.size() - 1)
    //             mvwprintw(window, cursorY, cursorX - 1, "|");
    //     }
    //     wrefresh(window);
    // }
    void activate();
    // {
    //     active = true;
    // }
    void deactivate();
    // {
    //     active = false;
    // }
    void moveLeft();
    // {
    //     if (selection == 0)
    //         selection = buttons.size() - 1;
    //     else
    //         --selection;
    // }
    void moveRight();
    // {
    //     if (selection == (int)buttons.size() - 1)
    //         selection = 0;
    //     else
    //         ++selection;
    // }

    bool pressed(); // returns true if popUp was activated
    // {
    //     if (!active)
    //         throw std::runtime_error("unable to press topbar when it is inactive");
    //     return buttons[selection]->pressed();
    // }
};