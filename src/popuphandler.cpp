#include "popuphandler.h"

#include "popupmenu.h"

PopUpHandler::PopUpHandler(WINDOW *background, Restaurant *restaurant)
    : backgroundWindow(background), restaurant(restaurant)
{
}

void PopUpHandler::newTableNoOrderPopUpMenu(Table *table)
{
    windowStack.push(std::make_unique<NoOrderAssignedToTablePopUpMenu>(backgroundWindow, this, restaurant, table));
}

void PopUpHandler::newChangeWaiterPopUpMenu()
{

    windowStack.push(std::make_unique<ChangeWaiterPopUpMenu>(backgroundWindow, this, restaurant));
}

void PopUpHandler::newLocalOrdersPopUpMenu()
{
    windowStack.push(std::make_unique<LocalOrdersPopUpMenu>(backgroundWindow, this, restaurant));
}

void PopUpHandler::newRemoteOrdersPopUpMenu()
{
    windowStack.push(std::make_unique<RemoteOrdersPopUpMenu>(backgroundWindow, this, restaurant));
}

void PopUpHandler::newErrorPrompt(std::string message)
{
    windowStack.push(std::make_unique<ErrorPrompt>(backgroundWindow, this, message, 6, std::max(10, (int)message.size() + 2)));
}

bool PopUpHandler::closePopUpMenu()
{
    windowStack.pop();
    return windowStack.empty();
    // if (windowStack.size() == 1)
    // {
    //     windowStack.pop();
    //     tablePopUpMenu.reset();
    //     return true;
    // }
    // else
    // {
    //     PopUpMenu *windowToDelete = windowStack.top();
    //     windowStack.pop();

    //     if (dynamic_cast<TablePopUpMenu *>(windowToDelete))
    //         tablePopUpMenu.reset();
    //     else if (dynamic_cast<ChangeWaiterPopUpMenu *>(windowToDelete))
    //         changeWaiterPopUpMenu.reset();
    // }
    // return false;
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