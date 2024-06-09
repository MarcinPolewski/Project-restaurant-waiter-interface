#include "popupmenu.h"

#include "restaurant.h"

ChangeWaiterPopUpMenu::ChangeWaiterPopUpMenu(WINDOW *background, PopUpHandler *popUpHandler, UIRestaurant *rest)
    : PopUpMenu(background, popUpHandler, WAITER_POP_UP_HEIGHT, DEFAULT_WIDTH), restaurant(rest)
{
    int buttonX = startX() + BUTTON_SIDE_OFFSET;
    int buttonY = getbegy(window) + DEFAULT_SCROLL_SECTION_START_Y;
    scrollStartY = buttonY;

    for (auto it = rest->wtbegin(); it != rest->wtend(); ++it)
    {
        scrollableButtons.push_back(std::make_unique<ChangeWaiterButton>(BUTTON_HEIGHT, DEFAULT_WIDTH - 2 * BUTTON_SIDE_OFFSET, buttonY, buttonX, popUpHandler, restaurant, &(*it)));
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

LocalOrderPopUpMenu::LocalOrderPopUpMenu(WINDOW *background, PopUpHandler *popUpHandler, UIRestaurant *rest, LocalOrder *order)
    : PopUpMenu(background, popUpHandler, LOCAL_ORDER_POP_UP_HEIGHT, DEFAULT_WIDTH, NUMBER_OF_SCROLL_BUTTONS_ORDERS), restaurant(rest), order(order)
{

    int buttonX = startX() + BUTTON_SIDE_OFFSET;
    int buttonY = getbegy(window) + 8;

    scrollStartY = buttonY;
    for (auto it = order->oibegin(); it != order->oiend(); ++it)
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
    mvwprintw(window, yCoordinate++, BUTTON_SIDE_OFFSET, ("Table:  " + order->table.getPositionStr() + " Seats: " + order->table.getSeatsStr()).c_str());
    mvwprintw(window, yCoordinate++, BUTTON_SIDE_OFFSET, DEFAULT_WIDTH_DEVIDER);

    yCoordinate = ORDER_SCROLL_SECTION_START_Y + (NUMBER_OF_SCROLL_BUTTONS_ORDERS * BUTTON_HEIGHT);
    mvwprintw(window, yCoordinate, BUTTON_SIDE_OFFSET, DEFAULT_WIDTH_DEVIDER);
}

int i = 10;

void LocalOrderPopUpMenu::update()
{
    // // add new buttons
    // // add buttons once again
    // // use auto_initialize()

    scrollableButtons.clear();
    int buttonWidth = DEFAULT_WIDTH - 2 * BUTTON_SIDE_OFFSET;

    int buttonX = startX() + BUTTON_SIDE_OFFSET;
    int buttonY = getbegy(window) + 4;

    for (auto it = order->oibegin(); it != order->oiend(); ++it)
    {
        scrollableButtons.push_back(std::make_unique<OrderItemButton>(BUTTON_HEIGHT, DEFAULT_WIDTH - 2 * BUTTON_SIDE_OFFSET, buttonY, buttonX, popUpHandler, &(*it)));
    }
    auto_initialize();
}

void LocalOrderPopUpMenu::buttonPressed()
{
    (*selectedButton)->deactivate();
    (*selectedButton)->pressed();
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

NoOrderAssignedToTablePopUpMenu::NoOrderAssignedToTablePopUpMenu(WINDOW *background, PopUpHandler *popUpHandler, UIRestaurant *rest, Table *table)
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

LocalOrdersPopUpMenu::LocalOrdersPopUpMenu(WINDOW *background, PopUpHandler *popUpHandler, UIRestaurant *restaurant)
    : PopUpMenu(background, popUpHandler, ORDERS_POP_UP_HEIGHT, DEFAULT_WIDTH, NUMBER_OF_SCROLL_BUTTONS_MENU), restaurant(restaurant)
{

    int buttonX = startX() + BUTTON_SIDE_OFFSET;
    int buttonY = getbegy(window) + BUTTON_TOP_OFFSET;
    int buttonWidth = DEFAULT_WIDTH - 2 * BUTTON_SIDE_OFFSET;

    Waiter::LOiterator it = restaurant->getCurrentWaiter()->lobegin_inprogress();
    Waiter::LOiterator ed = restaurant->getCurrentWaiter()->loend();

    scrollStartY = buttonY;
    for (; it != ed; ++it)
    {
        scrollableButtons.push_back(std::make_unique<LocalOrderButton>(BUTTON_HEIGHT, buttonWidth, buttonY, buttonX, popUpHandler, &(*it)));
    }

    buttonY = endY() - BUTTON_HEIGHT;
    staticButtons.push_back(std::make_unique<CloseButton>(BUTTON_HEIGHT, buttonWidth, buttonY, buttonX, popUpHandler));

    auto_initialize();
}

void LocalOrdersPopUpMenu::drawInformation()
{
    int yCoordinate = DEFAULT_TEXT_SECTION_START_Y;

    mvwprintw(window, yCoordinate++, BUTTON_SIDE_OFFSET, "Use arrow keys to navigate the menu.");
    mvwprintw(window, yCoordinate++, BUTTON_SIDE_OFFSET, "Press enter for further information");
    mvwprintw(window, yCoordinate++, BUTTON_SIDE_OFFSET, DEFAULT_WIDTH_DEVIDER);
}

RemoteOrdersPopUpMenu::RemoteOrdersPopUpMenu(WINDOW *background, PopUpHandler *popUpHandler, UIRestaurant *restaurant)
    : PopUpMenu(background, popUpHandler, ORDERS_POP_UP_HEIGHT, DEFAULT_WIDTH), restaurant(restaurant)
{

    int buttonX = startX() + BUTTON_SIDE_OFFSET;
    int buttonY = getbegy(window) + BUTTON_TOP_OFFSET;

    // TODO add order buttons here

    buttonY = endY() - BUTTON_HEIGHT;
    staticButtons.push_back(std::make_unique<CloseButton>(BUTTON_HEIGHT, DEFAULT_WIDTH - 2 * BUTTON_SIDE_OFFSET, buttonY, buttonX, popUpHandler));
    auto_initialize();
}

MenuItemView::MenuItemView(WINDOW *background, PopUpHandler *popUpHandler, MenuItem const &menuItem)
    : PopUpMenu(background, popUpHandler, MENU_ITEM_POP_UP_MENU_HEIGHT, MENU_ITEM_POP_UP_MENU_WIDTH), menuItem(menuItem)
{

    int buttonY = endY() - BUTTON_HEIGHT;
    int buttonX = startX() + BUTTON_SIDE_OFFSET;
    staticButtons.push_back(std::make_unique<CloseButton>(BUTTON_HEIGHT, MENU_ITEM_POP_UP_MENU_WIDTH - 2 * BUTTON_SIDE_OFFSET, buttonY, buttonX, popUpHandler));
    auto_initialize();
}

void MenuItemView::drawInformation()
{

    int maxTextWidth = MENU_ITEM_POP_UP_MENU_WIDTH - 2 * BUTTON_SIDE_OFFSET; // getmaxx(window) - 10; // Account for window borders
    int yCoordinate = DEFAULT_TEXT_SECTION_START_Y;

    mvwprintw(window, yCoordinate++, BUTTON_SIDE_OFFSET, ("name:   " + menuItem.name).c_str());
    mvwprintw(window, yCoordinate++, BUTTON_SIDE_OFFSET, ("price:  " + menuItem.getPriceStr()).c_str());
    mvwprintw(window, yCoordinate++, BUTTON_SIDE_OFFSET, ("volume: " + menuItem.getVolumeStr()).c_str());
    mvwprintw(window, yCoordinate++, BUTTON_SIDE_OFFSET, "description: ");
    // Split the product card into multiple lines if it exceeds the maximum width
    int lineCounter = 0;
    std::string description = menuItem.description;
    while (lineCounter++ != 2 && description.length() > maxTextWidth)
    {
        std::string line = description.substr(0, maxTextWidth);
        mvwprintw(window, yCoordinate++, BUTTON_SIDE_OFFSET, line.c_str());
        description = description.substr(maxTextWidth);
    }
    mvwprintw(window, yCoordinate++, BUTTON_SIDE_OFFSET, description.c_str());
}

OrderItemView::OrderItemView(WINDOW *background, PopUpHandler *popUpHandler, OrderItem *orderItem)
    : PopUpMenu(background, popUpHandler, ORDER_ITEM_POP_UP_MENU_HEIGHT, ORDER_ITEM_POP_UP_MENU_WIDTH), orderItem(orderItem)
{
    int buttonX = startX() + BUTTON_SIDE_OFFSET;
    int buttonY = getbegy(window) + BUTTON_TOP_OFFSET;
    int buttonWidth = ORDER_ITEM_POP_UP_MENU_WIDTH - (2 * BUTTON_SIDE_OFFSET);

    // TODO add order buttons here
    buttonY = endY() - 4 * BUTTON_HEIGHT;
    staticButtons.push_back(std::make_unique<setDeliveredButton>(BUTTON_HEIGHT, buttonWidth, buttonY, buttonX, popUpHandler, orderItem));
    buttonY += BUTTON_HEIGHT;
    staticButtons.push_back(std::make_unique<setCanceledButton>(BUTTON_HEIGHT, buttonWidth, buttonY, buttonX, popUpHandler, orderItem));
    buttonY += BUTTON_HEIGHT;
    staticButtons.push_back(std::make_unique<setDiscountPopUpMenuButton>(BUTTON_HEIGHT, buttonWidth, buttonY, buttonX, popUpHandler, orderItem));
    buttonY += BUTTON_HEIGHT;
    staticButtons.push_back(std::make_unique<CloseButton>(BUTTON_HEIGHT, buttonWidth, buttonY, buttonX, popUpHandler));

    auto_initialize();
}

void OrderItemView::drawInformation()
{
    int yCoordinate = DEFAULT_TEXT_SECTION_START_Y;

    mvwprintw(window, yCoordinate++, BUTTON_SIDE_OFFSET, ("Name:     " + orderItem->menuItem.name).c_str());
    mvwprintw(window, yCoordinate++, BUTTON_SIDE_OFFSET, ("Price:    " + orderItem->getPriceStr()).c_str());
    mvwprintw(window, yCoordinate++, BUTTON_SIDE_OFFSET, ("Quantity: " + orderItem->getQuantityStr()).c_str());
    mvwprintw(window, yCoordinate++, BUTTON_SIDE_OFFSET, ("Status:   " + orderItem->getStatusStr()).c_str());
    mvwprintw(window, yCoordinate++, BUTTON_SIDE_OFFSET, ("Discount: " + orderItem->getDiscountStr()).c_str());
    // mvwprintw(window, yCoordinate++, BUTTON_SIDE_OFFSEsT, ().c_str());
    // mvwprintw(window, yCoordinate++, BUTTON_SIDE_OFFSET, ().c_str());
    mvwprintw(window, yCoordinate++, BUTTON_SIDE_OFFSET, ORDER_ITEM_VIEW_DIVIDER);
}

SetDisciountPopUpMenu::SetDisciountPopUpMenu(WINDOW *background, PopUpHandler *popUpHandler, OrderItem *orderItem)
    : PopUpMenu(background, popUpHandler, ORDER_ITEM_POP_UP_MENU_HEIGHT, ORDER_ITEM_POP_UP_MENU_WIDTH, NUMBER_OF_BUTTONS_IN_SCROLL_DISCOUNT),
      orderItem(orderItem)
{
    int buttonX = startX() + BUTTON_SIDE_OFFSET;
    int buttonY = getbegy(window) + BUTTON_TOP_OFFSET;
    int buttonWidth = ORDER_ITEM_POP_UP_MENU_WIDTH - (2 * BUTTON_SIDE_OFFSET);

    scrollStartY = buttonY;
    for (unsigned int i = 0; i <= 100; i += 10)
    {
        scrollableButtons.push_back(std::make_unique<setDiscountButton>(BUTTON_HEIGHT, buttonWidth, buttonY, buttonX, popUpHandler, orderItem, i));
        // scrollableButtons.push_back(std::make_unique<AButton>(BUTTON_HEIGHT, DEFAULT_WIDTH - 2 * BUTTON_SIDE_OFFSET, buttonY, buttonX, popUpHandler));
        // scrollableButtons.push_back(std::make_unique<BButton>(BUTTON_HEIGHT, DEFAULT_WIDTH - 2 * BUTTON_SIDE_OFFSET, buttonY, buttonX, popUpHandler));
    }

    // TODO add order buttons here
    buttonY = endY() - BUTTON_HEIGHT;
    staticButtons.push_back(std::make_unique<CloseButton>(BUTTON_HEIGHT, buttonWidth, buttonY, buttonX, popUpHandler));
    auto_initialize();
}

SetQuantityPopUpMenu::SetQuantityPopUpMenu(WINDOW *background, PopUpHandler *popUpHandler, Order *order, MenuItem const &menuItem)
    : PopUpMenu(background, popUpHandler, ORDER_ITEM_POP_UP_MENU_HEIGHT, ORDER_ITEM_POP_UP_MENU_WIDTH, NUMBER_OF_BUTTONS_IN_SCROLL_DISCOUNT), order(order), menuItem(menuItem)
{
    int buttonX = startX() + BUTTON_SIDE_OFFSET;
    int buttonY = getbegy(window) + BUTTON_TOP_OFFSET;
    int buttonWidth = ORDER_ITEM_POP_UP_MENU_WIDTH - (2 * BUTTON_SIDE_OFFSET);

    scrollStartY = buttonY;
    for (unsigned int i = 1; i <= 10; ++i)
    {
        scrollableButtons.push_back(std::make_unique<SelectQuantityButton>(BUTTON_HEIGHT, buttonWidth, buttonY, buttonX, popUpHandler, order, menuItem, i));
    }

    // TODO add order buttons here
    buttonY = endY() - BUTTON_HEIGHT;
    staticButtons.push_back(std::make_unique<CloseButton>(BUTTON_HEIGHT, buttonWidth, buttonY, buttonX, popUpHandler));

    auto_initialize();
}