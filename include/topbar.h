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

    bool pressed();
    void update();
};

struct RemoteOrderTopBarButton : public TopBarButton
{
    Restaurant *restaurant;

public:
    RemoteOrderTopBarButton(PopUpHandler *popUpHandler, Restaurant *restaurant);

    bool pressed();
    void update();
};

class TopBar : public TerminalUIObject
{
    int selection = 0; // inx to currently pointed button
    std::vector<std::unique_ptr<TopBarButton>> buttons;
    bool active = true;
    PopUpHandler *popUpHandler;
    Restaurant *restaurant;
    void update();

public:
    TopBar(int height, int width, int positionY, int positionX, PopUpHandler *popUpHandler, Restaurant *restaurant);

    void draw() override;

    void activate();
    void deactivate();

    void moveLeft();
    void moveRight();

    bool pressed(); // returns true if popUp was activated
};