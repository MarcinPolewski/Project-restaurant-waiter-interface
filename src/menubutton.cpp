#include "menubutton.h"

#include "popuphandler.h"

void CloseButton::pressed()
{
    popUpHandler->closePopUpMenu();
}