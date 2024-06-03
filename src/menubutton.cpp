#include "menubutton.h"

#include "popuphandler.h"
#include "restaurant.h"

void CloseButton::pressed()
{
    popUpHandler->closePopUpMenu();
}

void ChangeWaiterButton::pressed()
{
    restaurant->changeCurrentWaiter(waiter);
}