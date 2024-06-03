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
    : TopBarButton(std::string("Change Waiter (" + restaurant->getCurrentWaiter()->toString() + ")"), popUpHandler), restaurant(restaurant) {}
bool ChangeWaiterTopBarButton::pressed()
{
    popUpHandler->newChangeWaiterPopUpMenu();
    return true;
}

void ChangeWaiterTopBarButton::update()
{
    // restaurant->getWaiters();
    //  restaurant->getCurrentWaiter();
    name = "Change Waiter (" + restaurant->getCurrentWaiter()->toString() + ")";
}

TopBar::TopBar(int height, int width, int positionY, int positionX, PopUpHandler *popUpHandler, Restaurant *restaurant)
    : TerminalUIObject(height, width, positionY, positionX), popUpHandler(popUpHandler), restaurant(restaurant)
{
    buttons.push_back(std::make_unique<ChangeWaiterTopBarButton>(popUpHandler, restaurant));
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