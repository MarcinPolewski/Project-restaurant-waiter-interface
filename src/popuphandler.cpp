#include "popuphandler.h"

#include "popupmenu.h"

PopUpHandler::PopUpHandler(WINDOW *background, Restaurant *restaurant)
    : backgroundWindow(background), restaurant(restaurant)
{
}

TablePopUpMenu *PopUpHandler::newTablePopUpMenu(UITable &table)
{
    tablePopUpMenu.reset(new TablePopUpMenu(backgroundWindow, this, table));
    windowStack.push(tablePopUpMenu.get());
    return tablePopUpMenu.get();
}

ChangeWaiterPopUpMenu *PopUpHandler::newChangeWaiterPopUpMenu()
{
    changeWaiterPopUpMenu.reset(new ChangeWaiterPopUpMenu(backgroundWindow, this, restaurant));
    windowStack.push(changeWaiterPopUpMenu.get());
    return changeWaiterPopUpMenu.get();
}

LocalOrdersPopUpMenu *PopUpHandler::newLocalOrdersPopUpMenu()
{
    localOrdersPopUpMenu.reset(new LocalOrdersPopUpMenu(backgroundWindow, this, restaurant));
    windowStack.push(localOrdersPopUpMenu.get());
    return localOrdersPopUpMenu.get();
}

bool PopUpHandler::closePopUpMenu()
{
    if (windowStack.size() == 1)
    {
        windowStack.pop();
        tablePopUpMenu.reset();
        return true;
    }
    else
    {
        PopUpMenu *windowToDelete = windowStack.top();
        windowStack.pop();

        if (dynamic_cast<TablePopUpMenu *>(windowToDelete))
            tablePopUpMenu.reset();
        else if (dynamic_cast<ChangeWaiterPopUpMenu *>(windowToDelete))
            changeWaiterPopUpMenu.reset();
    }
    return false;
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