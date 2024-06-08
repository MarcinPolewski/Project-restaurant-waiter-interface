#include "popupmenu.h"

#include "restaurant.h"

ChangeWaiterPopUpMenu::ChangeWaiterPopUpMenu(WINDOW *background, PopUpHandler *popUpHandler, Restaurant *rest)
    : PopUpMenu(background, popUpHandler, WAITER_POP_UP_HEIGHT, DEFAULT_WIDTH), restaurant(rest)
{
    int buttonX = startX() + BUTTON_SIDE_OFFSET;
    int buttonY = getbegy(window) + DEFAULT_SCROLL_SECTION_START_Y;
    scrollStartY = buttonY;

    std::vector<Waiter> &waiters = restaurant->getWaiters();

    for (auto &it : waiters)
    {
        scrollableButtons.push_back(std::make_unique<ChangeWaiterButton>(BUTTON_HEIGHT, DEFAULT_WIDTH - 2 * BUTTON_SIDE_OFFSET, buttonY, buttonX, popUpHandler, restaurant, &it));
        buttonY += BUTTON_HEIGHT;
    }

    buttonY = endY() - BUTTON_HEIGHT;
    staticButtons.push_back(std::make_unique<CloseButton>(BUTTON_HEIGHT, DEFAULT_WIDTH - 2 * BUTTON_SIDE_OFFSET, buttonY, buttonX, popUpHandler));
    auto_initialize();
}

void ChangeWaiterPopUpMenu::drawInformation()
{
    int yCoordinate = DEFAULT_TEXT_SECTION_START_Y;
    mvwprintw(window, yCoordinate++, BUTTON_SIDE_OFFSET, "Select current waiter using arrows");
    mvwprintw(window, yCoordinate++, BUTTON_SIDE_OFFSET, "and select with enter key");
    mvwprintw(window, yCoordinate++, BUTTON_SIDE_OFFSET, DEFAULT_WIDTH_DEVIDER);
    yCoordinate = (NUMBER_OF_BUTTONS_IN_SCROLL * BUTTON_HEIGHT) + DEFAULT_SCROLL_SECTION_START_Y;
    mvwprintw(window, yCoordinate, BUTTON_SIDE_OFFSET, DEFAULT_WIDTH_DEVIDER);
}

LocalOrderPopUpMenu::LocalOrderPopUpMenu(WINDOW *background, PopUpHandler *popUpHandler, Restaurant *rest, Order *order)
    : PopUpMenu(background, popUpHandler, LOCAL_ORDER_POP_UP_HEIGHT, DEFAULT_WIDTH, NUMBER_OF_SCROLL_BUTTONS_ORDERS), restaurant(rest), order(order)
{

    int buttonX = startX() + BUTTON_SIDE_OFFSET;
    int buttonY = getbegy(window) + 8;

    scrollStartY = buttonY;
    for (auto it = order->begin(); it != order->end(); ++it)
    {
        scrollableButtons.push_back(std::make_unique<OrderItemButton>(BUTTON_HEIGHT, DEFAULT_WIDTH - 2 * BUTTON_SIDE_OFFSET, buttonY, buttonX, popUpHandler, &(*it)));
        buttonY += BUTTON_HEIGHT;
    }

    buttonY = endY() - 3 * BUTTON_HEIGHT;
    staticButtons.push_back(std::make_unique<AddOrderItemButton>(BUTTON_HEIGHT, DEFAULT_WIDTH - 2 * BUTTON_SIDE_OFFSET, buttonY, buttonX, popUpHandler, order));
    buttonY += BUTTON_HEIGHT;
    staticButtons.push_back(std::make_unique<CloseOrderButton>(BUTTON_HEIGHT, DEFAULT_WIDTH - 2 * BUTTON_SIDE_OFFSET, buttonY, buttonX, popUpHandler, order));
    buttonY += BUTTON_HEIGHT;
    staticButtons.push_back(std::make_unique<CloseButton>(BUTTON_HEIGHT, DEFAULT_WIDTH - 2 * BUTTON_SIDE_OFFSET, buttonY, buttonX, popUpHandler));
    auto_initialize();
}

void LocalOrderPopUpMenu::drawInformation()
{
    int yCoordinate = DEFAULT_TEXT_SECTION_START_Y;
    mvwprintw(window, yCoordinate++, BUTTON_SIDE_OFFSET, "Order");
    mvwprintw(window, yCoordinate++, BUTTON_SIDE_OFFSET, DEFAULT_WIDTH_DEVIDER);
    mvwprintw(window, yCoordinate++, BUTTON_SIDE_OFFSET, ("Order time:   " + order->getOrderTimeStr()).c_str());
    mvwprintw(window, yCoordinate++, BUTTON_SIDE_OFFSET, ("Waiting time: " + order->getWaitingTimeStr()).c_str());
    mvwprintw(window, yCoordinate++, BUTTON_SIDE_OFFSET, ("Total price:  " + order->getTotalPriceStr()).c_str());
    mvwprintw(window, yCoordinate++, BUTTON_SIDE_OFFSET, DEFAULT_WIDTH_DEVIDER);

    yCoordinate = ORDER_SCROLL_SECTION_START_Y + (NUMBER_OF_SCROLL_BUTTONS_ORDERS * BUTTON_HEIGHT);
    mvwprintw(window, yCoordinate, BUTTON_SIDE_OFFSET, DEFAULT_WIDTH_DEVIDER);
}

void LocalOrderPopUpMenu::update()
{
    // // add new buttons
    // // add buttons once again
    // // use auto_initialize()

    scrollableButtons.clear();
    (*selectedButton)->deactivate();
    int buttonWidth = DEFAULT_WIDTH - 2 * BUTTON_SIDE_OFFSET;

    int buttonX = startX() + BUTTON_SIDE_OFFSET;
    int buttonY = getbegy(window) + 4;

    for (auto it = order->begin(); it != order->end(); ++it)
    {
        scrollableButtons.push_back(std::make_unique<OrderItemButton>(BUTTON_HEIGHT, DEFAULT_WIDTH - 2 * BUTTON_SIDE_OFFSET, buttonY, buttonX, popUpHandler, &(*it)));
    }
    auto_initialize();
}

MenuPopUpMenu::MenuPopUpMenu(WINDOW *background, PopUpHandler *popUpHandler, Menu const &menu)
    : PopUpMenu(background, popUpHandler, MENU_POP_UP_HEIGHT, DEFAULT_WIDTH, NUMBER_OF_SCROLL_BUTTONS_MENU), menu(menu)
{
    int buttonWidth = DEFAULT_WIDTH - 2 * BUTTON_SIDE_OFFSET;

    int buttonX = startX() + BUTTON_SIDE_OFFSET;
    int buttonY = getbegy(window) + 4;
    scrollStartY = buttonY;

    for (auto it = menu.mibegin(); it != menu.miend(); ++it)
    {
        scrollableButtons.push_back(std::make_unique<MenuItemButton>(BUTTON_HEIGHT, buttonWidth, buttonY, buttonX, popUpHandler, *it));
        buttonY += BUTTON_HEIGHT;
    }

    buttonY = endY() - BUTTON_HEIGHT;
    staticButtons.push_back(std::make_unique<CloseButton>(BUTTON_HEIGHT, buttonWidth, buttonY, buttonX, popUpHandler));
    auto_initialize();
}

void MenuPopUpMenu::drawInformation()
{
    int yCoordinate = DEFAULT_TEXT_SECTION_START_Y;
    mvwprintw(window, yCoordinate++, BUTTON_SIDE_OFFSET, "Use arrow keys to navigate the menu.");
    mvwprintw(window, yCoordinate++, BUTTON_SIDE_OFFSET, "Press enter for further information");
    mvwprintw(window, yCoordinate++, BUTTON_SIDE_OFFSET, DEFAULT_WIDTH_DEVIDER);
    yCoordinate = (NUMBER_OF_SCROLL_BUTTONS_MENU * BUTTON_HEIGHT) + DEFAULT_SCROLL_SECTION_START_Y;
    mvwprintw(window, yCoordinate, BUTTON_SIDE_OFFSET, DEFAULT_WIDTH_DEVIDER);
}

AddItemToOrderPopUpMenu::AddItemToOrderPopUpMenu(WINDOW *background, PopUpHandler *popUpHandler, Order *order, Menu const &menu)
    : PopUpMenu(background, popUpHandler, MENU_POP_UP_HEIGHT, DEFAULT_WIDTH, NUMBER_OF_SCROLL_BUTTONS_MENU), order(order), menu(menu)
{
    int buttonWidth = DEFAULT_WIDTH - 2 * BUTTON_SIDE_OFFSET;

    int buttonX = startX() + BUTTON_SIDE_OFFSET;
    int buttonY = getbegy(window) + 4;
    scrollStartY = buttonY;

    for (auto it = menu.mibegin(); it != menu.miend(); ++it)
    {
        scrollableButtons.push_back(std::make_unique<AddOrderItemToOrderButton>(BUTTON_HEIGHT, buttonWidth, buttonY, buttonX, popUpHandler, order, *it));
        buttonY += BUTTON_HEIGHT;
    }

    buttonY = endY() - BUTTON_HEIGHT;
    staticButtons.push_back(std::make_unique<CloseButton>(BUTTON_HEIGHT, buttonWidth, buttonY, buttonX, popUpHandler));
    auto_initialize();
}

void AddItemToOrderPopUpMenu::drawInformation()
{
    int yCoordinate = DEFAULT_TEXT_SECTION_START_Y;
    mvwprintw(window, yCoordinate++, BUTTON_SIDE_OFFSET, "Use arrow keys to navigate the menu.");
    mvwprintw(window, yCoordinate++, BUTTON_SIDE_OFFSET, "Press enter to select desired menu item to add");
    mvwprintw(window, yCoordinate++, BUTTON_SIDE_OFFSET, DEFAULT_WIDTH_DEVIDER);
    // yCoordinate = (NUMBER_OF_SCROLL_BUTTONS_MENU * BUTTON_HEIGHT) + DEFAULT_SCROLL_SECTION_START_Y;
    // mvwprintw(window, yCoordinate, BUTTON_SIDE_OFFSET, DEFAULT_WIDTH_DEVIDER);
}

ErrorPrompt::ErrorPrompt(WINDOW *background, PopUpHandler *popUpHandler, std::string message)
    : PopUpMenu(background, popUpHandler, TEXT_PROMPT_HEIGHT, message.size() + 2 * BUTTON_SIDE_OFFSET), message(message)
{
    int buttonX = startX() + BUTTON_SIDE_OFFSET;
    int buttonY = getbegy(window) + BUTTON_TOP_OFFSET;

    staticButtons.push_back(std::make_unique<CloseButton>(BUTTON_HEIGHT, getmaxx(window) - 2 * BUTTON_SIDE_OFFSET, buttonY, buttonX, popUpHandler, true));
    auto_initialize();
}

void ErrorPrompt::drawInformation()
{
    int yCoordinate = DEFAULT_TEXT_SECTION_START_Y;
    mvwprintw(window, yCoordinate, BUTTON_SIDE_OFFSET, message.c_str());
}

NoOrderAssignedToTablePopUpMenu::NoOrderAssignedToTablePopUpMenu(WINDOW *background, PopUpHandler *popUpHandler, Restaurant *rest, Table *table)
    : PopUpMenu(background, popUpHandler, NO_ORDER_ASSIGNED_POP_UP_HEIGHT, strlen(NO_ORDER_ASSIGNED_MESS) + 2), restaurant(rest), table(table)
{
    int buttonX = startX() + BUTTON_SIDE_OFFSET;
    int buttonY = getbegy(window) + BUTTON_TOP_OFFSET;

    staticButtons.push_back(std::make_unique<NewLocalOrderButton>(BUTTON_HEIGHT, getmaxx(window) - 2 * BUTTON_SIDE_OFFSET, buttonY, buttonX, popUpHandler, restaurant, table, true));
    buttonY += BUTTON_HEIGHT;
    staticButtons.push_back(std::make_unique<CloseButton>(BUTTON_HEIGHT, getmaxx(window) - 2 * BUTTON_SIDE_OFFSET, buttonY, buttonX, popUpHandler));
    auto_initialize();
}

void NoOrderAssignedToTablePopUpMenu::drawInformation()
{
    int yCoordinate = DEFAULT_TEXT_SECTION_START_Y;
    mvwprintw(window, yCoordinate, BUTTON_SIDE_OFFSET, NO_ORDER_ASSIGNED_MESS);
}

LocalOrdersPopUpMenu::LocalOrdersPopUpMenu(WINDOW *background, PopUpHandler *popUpHandler, Restaurant *restaurant)
    : PopUpMenu(background, popUpHandler, ORDERS_POP_UP_HEIGHT, DEFAULT_WIDTH), restaurant(restaurant)
{

    int buttonX = startX() + BUTTON_SIDE_OFFSET;
    int buttonY = getbegy(window) + BUTTON_TOP_OFFSET;

    // TODO add order buttons here
    scrollStartY = buttonY;
    for (int i = 0; i < 10; ++i)
    {
        // scrollableButtons.push_back(std::make_unique<AButton>(BUTTON_HEIGHT, DEFAULT_WIDTH - 2 * BUTTON_SIDE_OFFSET, buttonY, buttonX, popUpHandler));
        // scrollableButtons.push_back(std::make_unique<BButton>(BUTTON_HEIGHT, DEFAULT_WIDTH - 2 * BUTTON_SIDE_OFFSET, buttonY, buttonX, popUpHandler));
    }

    buttonY = endY() - BUTTON_HEIGHT;
    staticButtons.push_back(std::make_unique<CloseButton>(BUTTON_HEIGHT, DEFAULT_WIDTH - 2 * BUTTON_SIDE_OFFSET, buttonY, buttonX, popUpHandler));

    auto_initialize();
}

void LocalOrdersPopUpMenu::drawInformation()
{
    int yCoordinate = DEFAULT_TEXT_SECTION_START_Y;

    mvwprintw(window, yCoordinate++, BUTTON_SIDE_OFFSET, "Use arrow keys to navigate the menu.");
    mvwprintw(window, yCoordinate++, BUTTON_SIDE_OFFSET, "Press enter for further information");
    mvwprintw(window, yCoordinate++, BUTTON_SIDE_OFFSET, DEFAULT_WIDTH_DEVIDER);
}

RemoteOrdersPopUpMenu::RemoteOrdersPopUpMenu(WINDOW *background, PopUpHandler *popUpHandler, Restaurant *restaurant)
    : PopUpMenu(background, popUpHandler, ORDERS_POP_UP_HEIGHT, DEFAULT_WIDTH), restaurant(restaurant)
{

    int buttonX = startX() + BUTTON_SIDE_OFFSET;
    int buttonY = getbegy(window) + BUTTON_TOP_OFFSET;

    // TODO add order buttons here

    buttonY = endY() - BUTTON_HEIGHT;
    staticButtons.push_back(std::make_unique<CloseButton>(BUTTON_HEIGHT, DEFAULT_WIDTH - 2 * BUTTON_SIDE_OFFSET, buttonY, buttonX, popUpHandler));
    auto_initialize();
}
