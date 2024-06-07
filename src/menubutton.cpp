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
    // popUpHandler->newLocalOrderPopUpMenu( &(table->getOrder())); // przez te linie wywala teg fault, kwestia tego ze order nie jest przypisywany !!!! @TODO unhash
    //   kwestia tego ze referencja na table przestaje być aktualna??
}

void ChangeWaiterButton::pressed()
{
    restaurant->changeCurrentWaiter(waiter);
    popUpHandler->closePopUpMenu();
}

void OrderItemButton::pressed()
{
}