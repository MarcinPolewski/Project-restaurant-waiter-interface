#pragma once

#include <ncurses.h>
#include <stdexcept>
#include <stack>
#include <algorithm>

// #include "restaurant.h"
class Restaurant;
class PopUpMenu;
class ChangeWaiterPopUpMenu;
class LocalOrdersPopUpMenu;
class RemoteOrdersPopUpMenu;
class ErrorPrompt;
class UITable;
class LocalOrder;
class RemoteOrder;
class Table;
class Order;
struct MenuItem;
class OrderItem;

class PopUpHandler
{
    WINDOW *backgroundWindow;
    Restaurant *restaurant;
    std::stack<std::unique_ptr<PopUpMenu>> windowStack;

public:
    PopUpHandler(WINDOW *background, Restaurant *restaurant);

    void newLocalOrderPopUpMenu(LocalOrder *order);
    //  void newRemoteOrderPopUpMenu(RemoteOrder *order);
    void newTableNoOrderPopUpMenu(Table *table);
    void newAddItemToOrderPopUpMenu(Order *order);
    void newMenuItemView(MenuItem const &menuItem);
    void newOrderItemView(OrderItem *orderItem);
    void newSetDisciountPopUpMenu(OrderItem *orderItem);

    void newMenuPopUpMenu();
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