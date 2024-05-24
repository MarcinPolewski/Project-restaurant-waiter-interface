#include "restaurant.h"

Restaurant::Restaurant()
    : serverHandler(),
      menu(serverHandler.fetchMenu()),
      waiters(serverHandler.fetchWaiters()),
      tables(serverHandler.fetchTables())
{
    if (menu.empty())
        throw std::runtime_error("Menu cannot be empty");
    if (waiters.empty())
        throw std::runtime_error("Waiters list cannot be empty");

    currentWaiter = &waiters[0];
}

// dodać do serverhander metode allOrdersComplete - returns true if no ongoing orders

void Restaurant::changeCurrentWaiter(Waiter *waiter)
{
    currentWaiter = waiter;
}

Waiter const *Restaurant::getCurrentWaiter()
{
    return currentWaiter;
}

std::vector<Waiter> const &Restaurant::getWaiters()
{
    return waiters;
}
std::vector<Table> const &Restaurant::getTables()
{
    return tables;
}
Menu const &Restaurant::getMenu()
{
    return menu;
}