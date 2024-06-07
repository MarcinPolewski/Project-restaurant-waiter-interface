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
    if (order->empty())
        mvwprintw(window, 8, 1, "Order is empty");
    else
    {
        }

    wrefresh(window);
    // action button section ======
    int buttonX = startX() + BUTTON_SIDE_OFFSET;
    int buttonY = getbegy(window) + 20;

    buttons.push_back(std::make_unique<CloseButton>(BUTTON_HEIGHT, width - 2 * BUTTON_SIDE_OFFSET, buttonY, buttonX, popUpHandler, true));
}

ErrorPrompt::ErrorPrompt(WINDOW *background, PopUpHandler *popUpHandler, std::string message, int height, int width)
    : PopUpMenu(background, popUpHandler, height, width)
{

    // mvwprintw(window, buttonY, buttonX, message.c_str());
    mvwprintw(window, 1, 1, message.c_str());
    wrefresh(window);

    int buttonX = startX() + BUTTON_SIDE_OFFSET;
    int buttonY = getbegy(window) + BUTTON_TOP_OFFSET;

    buttons.push_back(std::make_unique<CloseButton>(BUTTON_HEIGHT, width - 2 * BUTTON_SIDE_OFFSET, buttonY, buttonX, popUpHandler, true));
}
NoOrderAssignedToTablePopUpMenu::NoOrderAssignedToTablePopUpMenu(WINDOW *background, PopUpHandler *popUpHandler, Restaurant *rest, Table *table, int height, int width)

    : PopUpMenu(background, popUpHandler, height, width), restaurant(rest), table(table)
{
    mvwprintw(window, 1, 1, NO_ORDER_ASSIGNED_MESS);
    wrefresh(window);

    int buttonX = startX() + BUTTON_SIDE_OFFSET;
    int buttonY = getbegy(window) + BUTTON_TOP_OFFSET;

    buttons.push_back(std::make_unique<NewLocalOrderButton>(BUTTON_HEIGHT, width - 2 * BUTTON_SIDE_OFFSET, buttonY, buttonX, popUpHandler, restaurant, table, true));
    buttonY += BUTTON_HEIGHT;
    buttons.push_back(std::make_unique<CloseButton>(BUTTON_HEIGHT, width - 2 * BUTTON_SIDE_OFFSET, buttonY, buttonX, popUpHandler));
}

LocalOrdersPopUpMenu::LocalOrdersPopUpMenu(WINDOW *background, PopUpHandler *popUpHandler, Restaurant *restaurant, int height, int width)
    : PopUpMenu(background, popUpHandler, height, width), restaurant(restaurant)
{

    int buttonX = startX() + BUTTON_SIDE_OFFSET;
    int buttonY = getbegy(window) + BUTTON_TOP_OFFSET;

    // TODO add order buttons here

    buttons.push_back(std::make_unique<CloseButton>(BUTTON_HEIGHT, width - 2 * BUTTON_SIDE_OFFSET, buttonY, buttonX, popUpHandler));
}

RemoteOrdersPopUpMenu::RemoteOrdersPopUpMenu(WINDOW *background, PopUpHandler *popUpHandler, Restaurant *restaurant, int height, int width)
    : PopUpMenu(background, popUpHandler, height, width), restaurant(restaurant)
{

    int buttonX = startX() + BUTTON_SIDE_OFFSET;
    int buttonY = getbegy(window) + BUTTON_TOP_OFFSET;

    // TODO add order buttons here

    buttons.push_back(std::make_unique<CloseButton>(BUTTON_HEIGHT, width - 2 * BUTTON_SIDE_OFFSET, buttonY, buttonX, popUpHandler));
}