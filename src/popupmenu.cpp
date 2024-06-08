#include "popupmenu.h"

#include "restaurant.h"

ChangeWaiterPopUpMenu::ChangeWaiterPopUpMenu(WINDOW *background, PopUpHandler *popUpHandler, Restaurant *rest, int height, int width)
    : PopUpMenu(background, popUpHandler, height, width), restaurant(rest)
{
    int buttonX = startX() + BUTTON_SIDE_OFFSET;
    int buttonY = getbegy(window) + BUTTON_TOP_OFFSET;

    std::vector<Waiter> &waiters = restaurant->getWaiters();

    scrollStartY = buttonY + 2;
    for (auto &it : waiters)
    {
        scrollableButtons.push_back(std::make_unique<ChangeWaiterButton>(BUTTON_HEIGHT, width - 2 * BUTTON_SIDE_OFFSET, buttonY, buttonX, popUpHandler, restaurant, &it));
        buttonY += BUTTON_HEIGHT;
    }

    buttonY = endY() - BUTTON_HEIGHT;
    staticButtons.push_back(std::make_unique<CloseButton>(BUTTON_HEIGHT, width - 2 * BUTTON_SIDE_OFFSET, buttonY, buttonX, popUpHandler));
    auto_initialize();
}

void ChangeWaiterPopUpMenu::drawInformation()
{
    mvwprintw(window, 1, 1, "Select current waiter using arrows");
    mvwprintw(window, 2, 1, "and select with enter key");
    mvwprintw(window, 3, 1, "--------------------");
}

LocalOrderPopUpMenu::LocalOrderPopUpMenu(WINDOW *background, PopUpHandler *popUpHandler, Restaurant *rest, Order *order, int height, int width)
    : PopUpMenu(background, popUpHandler, height, width), restaurant(rest), order(order)
{

    int buttonX = startX() + BUTTON_SIDE_OFFSET;
    int buttonY = getbegy(window) + 20;

    unsigned int cnt = 0;
    for (auto it = order->begin(); cnt != numberOfScrollButtonsOnScreen && it != order->end(); ++it, ++cnt)
    {
        staticButtons.push_back(std::make_unique<OrderItemButton>(BUTTON_HEIGHT, width - 2 * BUTTON_SIDE_OFFSET, buttonY, buttonX, popUpHandler, &(*it)));
        buttonY += BUTTON_HEIGHT;
    }

    staticButtons.push_back(std::make_unique<CloseButton>(BUTTON_HEIGHT, width - 2 * BUTTON_SIDE_OFFSET, buttonY, buttonX, popUpHandler, true));
    auto_initialize();
}

void LocalOrderPopUpMenu::drawInformation()
{
    mvwprintw(window, 1, 1, "Order");
    mvwprintw(window, 2, 1, "--------------------");
    mvwprintw(window, 3, 1, ("Order time:   " + order->getOrderTimeStr()).c_str());
    mvwprintw(window, 4, 1, ("Waiting time: " + order->getWaitingTimeStr()).c_str());
    mvwprintw(window, 5, 1, ("Total price:  " + order->getTotalPriceStr()).c_str());
    mvwprintw(window, 6, 1, "--------------------");

    if (order->empty())
        mvwprintw(window, scrollStartY, 1, "Order is empty");
}

MenuPopUpMenu::MenuPopUpMenu(WINDOW *background, PopUpHandler *popUpHandler, Menu const &menu, int height, int width)
    : PopUpMenu(background, popUpHandler, height, width, 10), menu(menu)
{

    // add menu buttons

    int buttonWidth = width - 2 * BUTTON_SIDE_OFFSET;

    int buttonX = startX() + BUTTON_SIDE_OFFSET;
    int buttonY = getbegy(window) + BUTTON_TOP_OFFSET;

    scrollStartY = buttonY;
    for (auto it = menu.mibegin(); it != menu.miend(); ++it)
    {
        scrollableButtons.push_back(std::make_unique<MenuItemButton>(BUTTON_HEIGHT, buttonWidth, buttonY, buttonX, popUpHandler, *it));
        buttonY += BUTTON_HEIGHT;
    }

    buttonY = endY() - BUTTON_HEIGHT - 1;
    staticButtons.push_back(std::make_unique<CloseButton>(BUTTON_HEIGHT, buttonWidth, buttonY, buttonX, popUpHandler));
    auto_initialize();
}

void MenuPopUpMenu::drawInformation()
{
    mvwprintw(window, 1, 1, "Use arrow keys to navigate the menu.");
    mvwprintw(window, 2, 1, "Press enter for further information");
}

ErrorPrompt::ErrorPrompt(WINDOW *background, PopUpHandler *popUpHandler, std::string message, int height, int width)
    : PopUpMenu(background, popUpHandler, height, width), message(message)
{
    int buttonX = startX() + BUTTON_SIDE_OFFSET;
    int buttonY = getbegy(window) + BUTTON_TOP_OFFSET;

    staticButtons.push_back(std::make_unique<CloseButton>(BUTTON_HEIGHT, width - 2 * BUTTON_SIDE_OFFSET, buttonY, buttonX, popUpHandler, true));
    auto_initialize();
}

void ErrorPrompt::drawInformation()
{
    mvwprintw(window, 1, 1, message.c_str());
}

NoOrderAssignedToTablePopUpMenu::NoOrderAssignedToTablePopUpMenu(WINDOW *background, PopUpHandler *popUpHandler, Restaurant *rest, Table *table, int height, int width)

    : PopUpMenu(background, popUpHandler, height, width), restaurant(rest), table(table)
{
    int buttonX = startX() + BUTTON_SIDE_OFFSET;
    int buttonY = getbegy(window) + BUTTON_TOP_OFFSET;

    staticButtons.push_back(std::make_unique<NewLocalOrderButton>(BUTTON_HEIGHT, width - 2 * BUTTON_SIDE_OFFSET, buttonY, buttonX, popUpHandler, restaurant, table, true));
    buttonY += BUTTON_HEIGHT;
    staticButtons.push_back(std::make_unique<CloseButton>(BUTTON_HEIGHT, width - 2 * BUTTON_SIDE_OFFSET, buttonY, buttonX, popUpHandler));
    auto_initialize();
}

void NoOrderAssignedToTablePopUpMenu::drawInformation()
{
    mvwprintw(window, 1, 1, NO_ORDER_ASSIGNED_MESS);
}

LocalOrdersPopUpMenu::LocalOrdersPopUpMenu(WINDOW *background, PopUpHandler *popUpHandler, Restaurant *restaurant, int height, int width)
    : PopUpMenu(background, popUpHandler, height, width), restaurant(restaurant)
{

    int buttonX = startX() + BUTTON_SIDE_OFFSET;
    int buttonY = getbegy(window) + BUTTON_TOP_OFFSET;

    // TODO add order buttons here
    scrollStartY = buttonY;
    for (int i = 0; i < 10; ++i)
    {
        scrollableButtons.push_back(std::make_unique<AButton>(BUTTON_HEIGHT, width - 2 * BUTTON_SIDE_OFFSET, buttonY, buttonX, popUpHandler));
        scrollableButtons.push_back(std::make_unique<BButton>(BUTTON_HEIGHT, width - 2 * BUTTON_SIDE_OFFSET, buttonY, buttonX, popUpHandler));
    }

    buttonY += 30;
    staticButtons.push_back(std::make_unique<CloseButton>(BUTTON_HEIGHT, width - 2 * BUTTON_SIDE_OFFSET, buttonY, buttonX, popUpHandler));

    auto_initialize();
}

void LocalOrdersPopUpMenu::drawInformation()
{
    mvwprintw(window, 1, 1, "Use arrow keys to navigate the menu.");
    mvwprintw(window, 2, 1, "Press enter for further information");
}

RemoteOrdersPopUpMenu::RemoteOrdersPopUpMenu(WINDOW *background, PopUpHandler *popUpHandler, Restaurant *restaurant, int height, int width)
    : PopUpMenu(background, popUpHandler, height, width), restaurant(restaurant)
{

    int buttonX = startX() + BUTTON_SIDE_OFFSET;
    int buttonY = getbegy(window) + BUTTON_TOP_OFFSET;

    // TODO add order buttons here

    staticButtons.push_back(std::make_unique<CloseButton>(BUTTON_HEIGHT, width - 2 * BUTTON_SIDE_OFFSET, buttonY, buttonX, popUpHandler));
    auto_initialize();
}
