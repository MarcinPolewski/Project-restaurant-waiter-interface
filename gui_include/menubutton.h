#pragma once
#include <ncurses.h>
#include <string>

#include "consoleuiobject.h"
#include "waiter.h"
// #include "popuphandler.h"

class PopUpHandler;
class UIRestaurant;

class MenuButton : public TerminalUIObject
{
protected:
    std::string title;
    bool selected = false;
    PopUpHandler *popUpHandler;

public:
    MenuButton(int height, int width, int yPosition, int xPosition, std::string title, PopUpHandler *popUpHandler, bool selected = false); // not passed by reference due to nature of initialization of buttons

    void draw() override;

    void activate();
    void deactivate();

    virtual void pressed() = 0;
};

class CloseButton : public MenuButton
{
public:
    CloseButton(int height, int width, int yPosition, int xPosition, PopUpHandler *popUpHandler, bool selected = false);
    void pressed() override;
};

class NewLocalOrderButton : public MenuButton
{
    UIRestaurant *restaurant;
    Table *table;

public:
    NewLocalOrderButton(int height, int width, int yPosition, int xPosition, PopUpHandler *popUpHandler, UIRestaurant *restaurant, Table *table, bool selected = false);
    void pressed() override;
};

class ChangeWaiterButton : public MenuButton
{
    Waiter *waiter;
    UIRestaurant *restaurant;

public:
    ChangeWaiterButton(int height, int width, int yPosition, int xPosition, PopUpHandler *popUpHandler, UIRestaurant *restaurant, Waiter *waiter, bool selected = false);
    void pressed() override;
};

class OrderItemButton : public MenuButton
{
    OrderItem *orderItem;

public:
    OrderItemButton(int height, int width, int yPosition, int xPosition, PopUpHandler *popUpHandler, OrderItem *orderItem, bool selected = false);

    void pressed() override;
};

class MenuItemButton : public MenuButton
{
    MenuItem const &menuItem;

public:
    MenuItemButton(int height, int width, int yPosition, int xPosition, PopUpHandler *popUpHandler, MenuItem const &menuItem, bool selected = false);
    void pressed() override;
};

class AddOrderItemButton : public MenuButton // button used to bring up menu, to add order item to order
{
    Order *order;

public:
    AddOrderItemButton(int height, int width, int yPosition, int xPosition, PopUpHandler *popUpHandler, Order *order, bool selected = false);
    void pressed() override;
};

class AddOrderItemToOrderButton : public MenuButton // represents specyfic menu item, when clicked it will be added to order
{
    Order *order;
    MenuItem const &menuItem;

public:
    AddOrderItemToOrderButton(int height, int width, int yPosition, int xPosition, PopUpHandler *popUpHandler, Order *order, MenuItem const &menuItem, bool selected = false);
    void pressed() override;
};

class CloseOrderButton : public MenuButton
{
    Order *order;

public:
    CloseOrderButton(int height, int width, int yPosition, int xPosition, PopUpHandler *popUpHandler, Order *order, bool selected = false);
    void pressed() override;
};

class setDeliveredButton : public MenuButton
{
    OrderItem *orderItem;

public:
    setDeliveredButton(int height, int width, int yPosition, int xPosition, PopUpHandler *popUpHandler, OrderItem *orderItem, bool selected = false);
    void pressed() override;
};
class setCanceledButton : public MenuButton
{
    OrderItem *orderItem;

public:
    setCanceledButton(int height, int width, int yPosition, int xPosition, PopUpHandler *popUpHandler, OrderItem *orderItem, bool selected = false);
    void pressed() override;
};

class setDiscountPopUpMenuButton : public MenuButton
{
    OrderItem *orderItem;

public:
    setDiscountPopUpMenuButton(int height, int width, int yPosition, int xPosition, PopUpHandler *popUpHandler, OrderItem *orderItem, bool selected = false);
    void pressed() override;
};

class setDiscountButton : public MenuButton
{
    OrderItem *orderItem;
    unsigned int discount;

public:
    setDiscountButton(int height, int width, int yPosition, int xPosition, PopUpHandler *popUpHandler, OrderItem *orderItem, unsigned int discount, bool selected = false);
    void pressed() override;
};

class LocalOrderButton : public MenuButton
{
    LocalOrder *order;

public:
    LocalOrderButton(int height, int width, int yPosition, int xPosition, PopUpHandler *popUpHandler, LocalOrder *order, bool selected = false);
    void pressed() override;
};

class SelectQuantityButton : public MenuButton
{
    Order *order;
    MenuItem const &menuItem;
    unsigned int quantity;

public:
    SelectQuantityButton(int height, int width, int yPosition, int xPosition, PopUpHandler *popUpHandler, Order *order, MenuItem const &menuItem, unsigned int quantity, bool selected = false);
    void pressed() override;
};