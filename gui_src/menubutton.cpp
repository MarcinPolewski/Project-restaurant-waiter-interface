#include "menubutton.h"

#include "popuphandler.h"
#include "restaurant.h"

// not passed by reference due to nature of initialization of buttons
MenuButton::MenuButton(int height, int width, int yPosition, int xPosition, std::string title, PopUpHandler *popUpHandler, bool selected)
    : TerminalUIObject(height, width, yPosition, xPosition), title(title), selected(selected), popUpHandler(popUpHandler)
{
}
void MenuButton::draw()
{
    box(window, 0, 0);
    if (selected)
        wattr_on(window, A_REVERSE, nullptr);
    mvwprintw(window, 1, 1, "%s", title.c_str());
    wattr_off(window, A_REVERSE, nullptr);

    wrefresh(window);
}
void MenuButton::activate()
{
    selected = true;
}

void MenuButton::deactivate()
{
    selected = false;
}

CloseButton::CloseButton(int height, int width, int yPosition, int xPosition, PopUpHandler *popUpHandler, bool selected)
    : MenuButton(height, width, yPosition, xPosition, std::string("Close"), popUpHandler, selected)
{
}

void CloseButton::pressed()
{
    popUpHandler->closePopUpMenu();
}

NewLocalOrderButton::NewLocalOrderButton(int height, int width, int yPosition, int xPosition, PopUpHandler *popUpHandler, UIRestaurant *restaurant, Table *table, bool selected)
    : MenuButton(height, width, yPosition, xPosition, std::string("Crete new Local Order"), popUpHandler, selected), restaurant(restaurant), table(table)
{
}

void NewLocalOrderButton::pressed()
{
    restaurant->newLocalOrder(*table);
    popUpHandler->closePopUpMenu(); // gdy to zakomentowane to dziala xd
}

MenuItemButton::MenuItemButton(int height, int width, int yPosition, int xPosition, PopUpHandler *popUpHandler, MenuItem const &menuItem, bool selected)
    : MenuButton(height, width, yPosition, xPosition, menuItem.name, popUpHandler, selected), menuItem(menuItem)
{
}

void MenuItemButton::pressed()
{
    popUpHandler->newMenuItemView(menuItem);
}

AddOrderItemButton::AddOrderItemButton(int height, int width, int yPosition, int xPosition, PopUpHandler *popUpHandler, Order *order, bool selected)
    : MenuButton(height, width, yPosition, xPosition, "Add item to order", popUpHandler, selected), order(order)
{
}

void AddOrderItemButton::pressed()
{
    popUpHandler->newAddItemToOrderPopUpMenu(order);
}

AddOrderItemToOrderButton::AddOrderItemToOrderButton(int height, int width, int yPosition, int xPosition, PopUpHandler *popUpHandler, Order *order, MenuItem const &menuItem, bool selected)
    : MenuButton(height, width, yPosition, xPosition, menuItem.name, popUpHandler, selected), order(order), menuItem(menuItem)
{
}

void AddOrderItemToOrderButton::pressed()
{
    popUpHandler->newSetQuantityPopUpMenu(order, menuItem);
}

CloseOrderButton::CloseOrderButton(int height, int width, int yPosition, int xPosition, PopUpHandler *popUpHandler, Order *order, bool selected)
    : MenuButton(height, width, yPosition, xPosition, "Close order", popUpHandler, selected), order(order)
{
}

void CloseOrderButton::pressed()
{
    try
    {
        order->setClosed();
        popUpHandler->closePopUpMenu();
    }
    catch (const std::exception &e)
    {
        std::string errorMessage = e.what();
        popUpHandler->newErrorPrompt(errorMessage);
    }
}
ChangeWaiterButton::ChangeWaiterButton(int height, int width, int yPosition, int xPosition, PopUpHandler *popUpHandler, UIRestaurant *restaurant, Waiter *waiter, bool selected)
    : MenuButton(height, width, yPosition, xPosition, waiter->toString(), popUpHandler, selected), waiter(waiter), restaurant(restaurant)
{
}

void ChangeWaiterButton::pressed()
{
    restaurant->changeCurrentWaiter(waiter);
    popUpHandler->closePopUpMenu();
}

OrderItemButton::OrderItemButton(int height, int width, int yPosition, int xPosition, PopUpHandler *popUpHandler, OrderItem *orderItem, bool selected)
    : MenuButton(height, width, yPosition, xPosition, orderItem->menuItem.name, popUpHandler, selected), orderItem(orderItem)
{
    title = orderItem->menuItem.name + " | quantity: " + orderItem->getQuantityStr() + " | total price: " + orderItem->getPriceStr();
}

void OrderItemButton::pressed()
{
    popUpHandler->newOrderItemView(orderItem);
}

setDeliveredButton::setDeliveredButton(int height, int width, int yPosition, int xPosition, PopUpHandler *popUpHandler, OrderItem *orderItem, bool selected)
    : MenuButton(height, width, yPosition, xPosition, "Set delivered", popUpHandler, selected), orderItem(orderItem)
{
}

void setDeliveredButton::pressed()
{
    try
    {
        orderItem->setDelivered();
        popUpHandler->closePopUpMenu();
    }

    catch (const std::exception &e)
    {
        std::string errorMessage = e.what();
        popUpHandler->newErrorPrompt(errorMessage);
    }
}

setCanceledButton::setCanceledButton(int height, int width, int yPosition, int xPosition, PopUpHandler *popUpHandler, OrderItem *orderItem, bool selected)
    : MenuButton(height, width, yPosition, xPosition, "Set canceled", popUpHandler, selected), orderItem(orderItem)
{
}

void setCanceledButton::pressed()
{

    try
    {
        orderItem->setCancelled();
        popUpHandler->closePopUpMenu();
    }

    catch (const std::exception &e)
    {
        std::string errorMessage = e.what();
        popUpHandler->newErrorPrompt(errorMessage);
    }
}

setDiscountPopUpMenuButton::setDiscountPopUpMenuButton(int height, int width, int yPosition, int xPosition, PopUpHandler *popUpHandler, OrderItem *orderItem, bool selected)
    : MenuButton(height, width, yPosition, xPosition, "Set discount", popUpHandler, selected), orderItem(orderItem)
{
}

void setDiscountPopUpMenuButton::pressed()
{
    popUpHandler->newSetDisciountPopUpMenu(orderItem);
}

setDiscountButton::setDiscountButton(int height, int width, int yPosition, int xPosition, PopUpHandler *popUpHandler, OrderItem *orderItem, unsigned int discount, bool selected)
    : MenuButton(height, width, yPosition, xPosition, (std::to_string(discount) + " percent").c_str(), popUpHandler, selected), orderItem(orderItem), discount(discount)
{
}

void setDiscountButton::pressed()
{
    try
    {
        orderItem->setDiscount(discount);
        popUpHandler->closePopUpMenu();
    }
    catch (const std::exception &e)
    {
        std::string errorMessage = e.what();
        popUpHandler->newErrorPrompt(errorMessage);
    }
}

LocalOrderButton::LocalOrderButton(int height, int width, int yPosition, int xPosition, PopUpHandler *popUpHandler, LocalOrder *order, bool selected)
    : MenuButton(height, width, yPosition, xPosition, "zamowienie", popUpHandler, selected), order(order)
{
    title = "table " + order->table.getPositionStr() + " | time " + order->getOrderTimeStr() + " | total " + order->getTotalPriceStr();
}

void LocalOrderButton::pressed()
{
    popUpHandler->newLocalOrderPopUpMenu(order);
}

SelectQuantityButton::SelectQuantityButton(int height, int width, int yPosition, int xPosition, PopUpHandler *popUpHandler, Order *order, MenuItem const &menuItem, unsigned int quantity, bool selected)
    : MenuButton(height, width, yPosition, xPosition, std::to_string(quantity), popUpHandler, selected), order(order), menuItem(menuItem), quantity(quantity)
{
}

void SelectQuantityButton::pressed()
{
    order->addOrderItem(menuItem, quantity);
    popUpHandler->closePopUpMenu();
}