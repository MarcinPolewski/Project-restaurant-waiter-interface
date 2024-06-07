#include "menubutton.h"

#include "popuphandler.h"
#include "restaurant.h"

void CloseButton::pressed()
{
    popUpHandler->closePopUpMenu();
}

void NewLocalOrderButton::pressed()
{
    restaurant->newLocalOrder(table);
    // popUpHandler->newLocalOrdersPopUpMenu(table->order);
}

void ChangeWaiterButton::pressed()
{
    restaurant->changeCurrentWaiter(waiter);
    popUpHandler->closePopUpMenu();
}