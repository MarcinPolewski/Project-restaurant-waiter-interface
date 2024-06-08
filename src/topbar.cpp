#include "topbar.h"

#include "consoleuiobject.h"
#include "popuphandler.h"
#include "restaurant.h"
#include "waiter.h"

TopBarButton::TopBarButton(std::string name, PopUpHandler *popUpHandler) // string not passed by reference due to nature of it's use
    : name(name), popUpHandler(popUpHandler)
{
}

ChangeWaiterTopBarButton::ChangeWaiterTopBarButton(PopUpHandler *popUpHandler, Restaurant *restaurant)
    : TopBarButton(std::string("Change Waiter (" + restaurant->getCurrentWaiter()->toString() + ")"), popUpHandler),
      restaurant(restaurant) {}
bool ChangeWaiterTopBarButton::pressed()
{
    popUpHandler->newChangeWaiterPopUpMenu();
    return true;
}

void ChangeWaiterTopBarButton::update()
{
    name = "Change Waiter (" + restaurant->getCurrentWaiter()->toString() + ")";
}

RemoteOrderTopBarButton::RemoteOrderTopBarButton(PopUpHandler *popUpHandler, Restaurant *restaurant)
    : TopBarButton(std::string("Remote Orders (" + std::to_string(restaurant->remoteOrdersCount()) + ")"), popUpHandler),
      restaurant(restaurant) {}

bool RemoteOrderTopBarButton::pressed()
{
    popUpHandler->newRemoteOrdersPopUpMenu();
    return true;
}
void RemoteOrderTopBarButton::update()
{
    name = "Remote Orders (" + std::to_string(restaurant->remoteOrdersCount()) + ")";
}

LocalOrderTopBarButton::LocalOrderTopBarButton(PopUpHandler *popUpHandler, Restaurant *restaurant)
    : TopBarButton(std::string("Local Orders (" + std::to_string(restaurant->localOrdersCount()) + ")"), popUpHandler),
      restaurant(restaurant) {}

bool LocalOrderTopBarButton::pressed()
{
    popUpHandler->newLocalOrdersPopUpMenu();
    return true;
}
void LocalOrderTopBarButton::update()
{
    name = "Local Orders (" + std::to_string(restaurant->localOrdersCount()) + ")";
}

MenuTopBarButton::MenuTopBarButton(PopUpHandler *popUpHandler)
    : TopBarButton(std::string("Menu"), popUpHandler)
{
}
bool MenuTopBarButton::pressed()
{
    popUpHandler->newMenuPopUpMenu();
    return true;
}

CloseOrderTopBarButton::CloseOrderTopBarButton(PopUpHandler *popUpHandler, Restaurant *restaurant)
    : TopBarButton(std::string("Close Restaurant"), popUpHandler),
      restaurant(restaurant) {}

bool CloseOrderTopBarButton::pressed()
{
    // check if can be closed
    if (restaurant->canBeClosed())
        restaurant->close();
    else
        popUpHandler->newErrorPrompt(std::string("Cannot close restaurant, orders are still in progress."));
    return true;
}
TopBar::TopBar(int height, int width, int positionY, int positionX, PopUpHandler *popUpHandler, Restaurant *restaurant)
    : TerminalUIObject(height, width, positionY, positionX), popUpHandler(popUpHandler), restaurant(restaurant)
{
    buttons.push_back(std::make_unique<ChangeWaiterTopBarButton>(popUpHandler, restaurant));
    buttons.push_back(std::make_unique<RemoteOrderTopBarButton>(popUpHandler, restaurant));
    buttons.push_back(std::make_unique<LocalOrderTopBarButton>(popUpHandler, restaurant));
    buttons.push_back(std::make_unique<MenuTopBarButton>(popUpHandler));
    buttons.push_back(std::make_unique<CloseOrderTopBarButton>(popUpHandler, restaurant));

    draw();
}

void TopBar::update()
{
    for (auto &it : buttons)
        it->update();
}

void TopBar::draw()
{
    wclear(window);
    update();
    box(window, 0, 0);
    int width = getmaxx(window);
    int widthPerButton = width / buttons.size();

    // ============== draw buttons to window
    int cursorX = 1;
    int cursorY = 1;

    for (int i = 0; i < (int)buttons.size(); i++)
    {

        // calculate button position offset from the left
        int offset = (widthPerButton - buttons[i]->toString().size()) / 2;

        if (active && i == selection) // print menu as selected if neccessary
            wattr_on(window, A_REVERSE, nullptr);
        mvwprintw(window, cursorY, cursorX + offset, buttons[i]->toString().c_str());
        wattr_off(window, A_REVERSE, nullptr);
        cursorX += widthPerButton;
        if (i != (int)buttons.size() - 1)
            mvwprintw(window, cursorY, cursorX - 1, "|");
    }
    wrefresh(window);
}

void TopBar::activate()
{
    active = true;
}
void TopBar::deactivate()
{
    active = false;
}
void TopBar::moveLeft()
{
    if (selection == 0)
        selection = buttons.size() - 1;
    else
        --selection;
}
void TopBar::moveRight()
{
    if (selection == (int)buttons.size() - 1)
        selection = 0;
    else
        ++selection;
}

bool TopBar::pressed() // returns true if popUp was activated
{
    if (!active)
        throw std::runtime_error("unable to press topbar when it is inactive");
    return buttons[selection]->pressed();
}