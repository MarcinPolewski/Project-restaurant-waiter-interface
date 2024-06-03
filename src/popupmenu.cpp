#include "popupmenu.h"

#include "restaurant.h"

ChangeWaiterPopUpMenu::ChangeWaiterPopUpMenu(WINDOW *background, PopUpHandler *popUpHandler, Restaurant *rest, int height, int width)
    : PopUpMenu(background, popUpHandler, height, width), restaurant(rest)
{
    int buttonX = startX() + BUTTON_SIDE_OFFSET;
    int buttonY = getbegy(window) + BUTTON_TOP_OFFSET;

    std::vector<Waiter> &waiters = restaurant->getWaiters();
    for (auto &it : waiters)
    {
        buttons.push_back(std::make_unique<ChangeWaiterButton>(BUTTON_HEIGHT, width - 2 * BUTTON_SIDE_OFFSET, buttonY, buttonX, popUpHandler, restaurant, &it));
        buttonY += BUTTON_HEIGHT;
    }

    buttons[0]->activate();
    buttons[0]->draw();

    buttons.push_back(std::make_unique<CloseButton>(BUTTON_HEIGHT, width - 2 * BUTTON_SIDE_OFFSET, buttonY, buttonX, popUpHandler));
}