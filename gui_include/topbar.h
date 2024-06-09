#pragma once

#include <ncurses.h>
#include <vector>

#include "consoleuiobject.h"

class PopUpHandler;
class UIRestaurant;
class Waiter;

class TopBarButton
{
protected:
    std::string name;

public:
    PopUpHandler *popUpHandler;
    TopBarButton(std::string name, PopUpHandler *popUpHandler); // string not passed by reference due to nature of it's use

    virtual std::string toString() { return name; }
    virtual bool pressed() = 0;
    virtual void update()
    {
    }
    virtual ~TopBarButton() = default;
};

class ChangeWaiterTopBarButton : public TopBarButton
{
    UIRestaurant *restaurant;

public:
    ChangeWaiterTopBarButton(PopUpHandler *popUpHandler, UIRestaurant *restaurant);

    bool pressed() override;
    void update() override;
};

class RemoteOrderTopBarButton : public TopBarButton
{
    UIRestaurant *restaurant;

public:
    RemoteOrderTopBarButton(PopUpHandler *popUpHandler, UIRestaurant *restaurant);

    bool pressed() override;
    void update() override;
};

class LocalOrderTopBarButton : public TopBarButton
{
    UIRestaurant *restaurant;

public:
    LocalOrderTopBarButton(PopUpHandler *popUpHandler, UIRestaurant *restaurant);

    bool pressed() override;
    void update() override;
};

class MenuTopBarButton : public TopBarButton
{

public:
    MenuTopBarButton(PopUpHandler *popUpHandler);

    bool pressed() override;
};

class CloseOrderTopBarButton : public TopBarButton
{
    UIRestaurant *restaurant;

public:
    CloseOrderTopBarButton(PopUpHandler *popUpHandler, UIRestaurant *restaurant);

    bool pressed();
};

class TopBar : public TerminalUIObject
{
    int selection = 0; // inx to currently pointed button
    std::vector<std::unique_ptr<TopBarButton>> buttons;
    bool active = true;
    PopUpHandler *popUpHandler;
    UIRestaurant *restaurant;
    void update();

public:
    TopBar(int height, int width, int positionY, int positionX, PopUpHandler *popUpHandler, UIRestaurant *restaurant);

    void draw() override;

    void activate();
    void deactivate();

    void moveLeft();
    void moveRight();

    bool pressed(); // returns true if popUp was activated
};