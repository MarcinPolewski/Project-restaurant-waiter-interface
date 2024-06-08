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
        staticButtons.push_back(std::make_unique<ChangeWaiterButton>(BUTTON_HEIGHT, width - 2 * BUTTON_SIDE_OFFSET, buttonY, buttonX, popUpHandler, restaurant, &it));
        buttonY += BUTTON_HEIGHT;
    }

    staticButtons[0]->activate();
    staticButtons[0]->draw();

    staticButtons.push_back(std::make_unique<CloseButton>(BUTTON_HEIGHT, width - 2 * BUTTON_SIDE_OFFSET, buttonY, buttonX, popUpHandler));
    auto_initialize();
}

LocalOrderPopUpMenu::LocalOrderPopUpMenu(WINDOW *background, PopUpHandler *popUpHandler, Restaurant *rest, Order *order, int height, int width)
    : PopUpMenu(background, popUpHandler, height, width), restaurant(rest), order(order)
{

    // information section =========
    mvwprintw(window, 1, 1, "Order");
    mvwprintw(window, 2, 1, "--------------------");
    mvwprintw(window, 3, 1, ("Order time:   " + order->getOrderTimeStr()).c_str());
    mvwprintw(window, 4, 1, ("Waiting time: " + order->getWaitingTimeStr()).c_str());
    mvwprintw(window, 5, 1, ("Total price:  " + order->getTotalPriceStr()).c_str());
    mvwprintw(window, 6, 1, "--------------------");

    // order item srcoll section ==========

    int buttonX = startX() + BUTTON_SIDE_OFFSET;
    int buttonY = getbegy(window) + 20;

    if (order->empty())
        mvwprintw(window, 8, 1, "Order is empty");
    else
    {
        unsigned int cnt = 0;
        for (auto it = order->begin(); cnt != NUMBER_OF_BUTTONS_IN_SCROLL && it != order->end(); ++it, ++cnt)
        {
            staticButtons.push_back(std::make_unique<OrderItemButton>(BUTTON_HEIGHT, width - 2 * BUTTON_SIDE_OFFSET, buttonY, buttonX, popUpHandler, &(*it)));
            buttonY += BUTTON_HEIGHT;
        }
    }

    // wrefresh(window);
    //  action button section ======

    staticButtons.push_back(std::make_unique<CloseButton>(BUTTON_HEIGHT, width - 2 * BUTTON_SIDE_OFFSET, buttonY, buttonX, popUpHandler, true));
    auto_initialize();
}

ErrorPrompt::ErrorPrompt(WINDOW *background, PopUpHandler *popUpHandler, std::string message, int height, int width)
    : PopUpMenu(background, popUpHandler, height, width)
{

    // mvwprintw(window, buttonY, buttonX, message.c_str());
    mvwprintw(window, 1, 1, message.c_str());
    // wrefresh(window);

    int buttonX = startX() + BUTTON_SIDE_OFFSET;
    int buttonY = getbegy(window) + BUTTON_TOP_OFFSET;

    staticButtons.push_back(std::make_unique<CloseButton>(BUTTON_HEIGHT, width - 2 * BUTTON_SIDE_OFFSET, buttonY, buttonX, popUpHandler, true));
    auto_initialize();
}
NoOrderAssignedToTablePopUpMenu::NoOrderAssignedToTablePopUpMenu(WINDOW *background, PopUpHandler *popUpHandler, Restaurant *rest, Table *table, int height, int width)

    : PopUpMenu(background, popUpHandler, height, width), restaurant(rest), table(table)
{
    mvwprintw(window, 1, 1, NO_ORDER_ASSIGNED_MESS);
    // wrefresh(window);

    int buttonX = startX() + BUTTON_SIDE_OFFSET;
    int buttonY = getbegy(window) + BUTTON_TOP_OFFSET;

    staticButtons.push_back(std::make_unique<NewLocalOrderButton>(BUTTON_HEIGHT, width - 2 * BUTTON_SIDE_OFFSET, buttonY, buttonX, popUpHandler, restaurant, table, true));
    buttonY += BUTTON_HEIGHT;
    staticButtons.push_back(std::make_unique<CloseButton>(BUTTON_HEIGHT, width - 2 * BUTTON_SIDE_OFFSET, buttonY, buttonX, popUpHandler));
    auto_initialize();
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

    // staticButtons.push_back(std::make_unique<CloseButton>(BUTTON_HEIGHT, width - 2 * BUTTON_SIDE_OFFSET, buttonY, buttonX, popUpHandler));
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