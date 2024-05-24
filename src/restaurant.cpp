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

void Restaurant::closeRestaurant()
{
    for (auto it : waiters)
    {
        if (it.hasOrders())
            throw std::runtime_error("cannot cloase restaurant, when some orders are still in progress");
    }
}

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