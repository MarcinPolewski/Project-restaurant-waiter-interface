#include "menubutton.h"

#include "popuphandler.h"
#include "restaurant.h"

void CloseButton::pressed()
{
    popUpHandler->closePopUpMenu();
}

void NewLocalOrderButton::pressed()
{
    restaurant->newLocalOrder(*table);
    popUpHandler->closePopUpMenu(); // gdy to zakomentowane to dziala xd
}

void MenuItemButton::pressed()
{
    popUpHandler->newMenuItemView(menuItem);
}

void AddOrderItemButton::pressed()
{
    popUpHandler->newAddItemToOrderPopUpMenu(order);
}

void AddOrderItemToOrderButton::pressed()
{
    order->addOrderItem(menuItem, 1);
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

void ChangeWaiterButton::pressed()
{
    restaurant->changeCurrentWaiter(waiter);
    popUpHandler->closePopUpMenu();
}

void OrderItemButton::pressed()
{
    popUpHandler->newOrderItemView(orderItem);
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

void setDiscountPopUpMenuButton::pressed()
{
    popUpHandler->newSetDisciountPopUpMenu(orderItem);
}

void setDiscountButton::pressed()
{
    orderItem->setDiscount(discount);
    popUpHandler->closePopUpMenu();
}