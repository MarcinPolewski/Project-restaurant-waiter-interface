#include "popuphandler.h"

#include "popupmenu.h"

#include "restaurant.h"

PopUpHandler::PopUpHandler(WINDOW *background, Restaurant *restaurant)
    : backgroundWindow(background), restaurant(restaurant)
{
}

void PopUpHandler::newLocalOrderPopUpMenu(LocalOrder *order)
{
    windowStack.push(std::make_unique<LocalOrderPopUpMenu>(backgroundWindow, this, restaurant, order));
    windowStack.top()->draw();
}

void PopUpHandler::newTableNoOrderPopUpMenu(Table *table)
{
    windowStack.push(std::make_unique<NoOrderAssignedToTablePopUpMenu>(backgroundWindow, this, restaurant, table));
    windowStack.top()->draw();
}

void PopUpHandler::newMenuPopUpMenu()
{
    windowStack.push(std::make_unique<MenuPopUpMenu>(backgroundWindow, this, restaurant->getMenu()));
    windowStack.top()->draw();
}

void PopUpHandler::newChangeWaiterPopUpMenu()
{

    windowStack.push(std::make_unique<ChangeWaiterPopUpMenu>(backgroundWindow, this, restaurant));
    windowStack.top()->draw();
}

void PopUpHandler::newLocalOrdersPopUpMenu()
{
    windowStack.push(std::make_unique<LocalOrdersPopUpMenu>(backgroundWindow, this, restaurant));
    windowStack.top()->draw();
}

void PopUpHandler::newRemoteOrdersPopUpMenu()
{
    windowStack.push(std::make_unique<RemoteOrdersPopUpMenu>(backgroundWindow, this, restaurant));
    windowStack.top()->draw();
}

void PopUpHandler::newErrorPrompt(std::string message)
{
    windowStack.push(std::make_unique<ErrorPrompt>(backgroundWindow, this, message));
    windowStack.top()->draw();
}

bool PopUpHandler::closePopUpMenu()
{
    windowStack.pop();
    return windowStack.empty();
}

void PopUpHandler::moveUp()
{
    if (windowStack.empty())
        throw std::invalid_argument("no popup is displayed");
    windowStack.top()->moveUp();
}

void PopUpHandler::moveDown()
{
    if (windowStack.empty())
        throw std::invalid_argument("no popup is displayed");
    windowStack.top()->moveDown();
}

void PopUpHandler::draw()
{
    if (!windowStack.empty())
        windowStack.top()->draw();
}

bool PopUpHandler::buttonPressed()
{
    if (windowStack.empty())
        throw std::invalid_argument("no popup is displayed");
    windowStack.top()->buttonPressed();

    // figure out which menu it is
    // get input

    if (windowStack.empty())
        return true;
    return false;
    // gdybysmy tutaj mieli to, co zostalo wcisniete, to
    // mozna duzo z tym zrobic, wywolac nowe okno co cos zwraca
    // mozna porobic dynamic casty, zeby wiedziec jakie to menu i jakie ma guziki
    // how to interact with mainLoop ??
    // necessary when closing, switching modes(the same as close)
}