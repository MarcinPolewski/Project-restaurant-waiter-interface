#include "restaurant.h"

Restaurant::Restaurant()
    : memoryHandler(),
      serverHandler(memoryHandler),
      menu(memoryHandler.fetchMenu()),
      waiters(memoryHandler.fetchWaiters()),
      tables(memoryHandler.fetchTables())
{
    if (menu.empty())
        throw std::runtime_error("Menu cannot be empty");
    if (waiters.empty())
        throw std::runtime_error("Waiters list cannot be empty");

    currentWaiter = &waiters[0];
}

RemoteOrder *Restaurant::newRemoteOrder(Remote *remote)
{
    remoteOrders.push_back(RemoteOrder(*remote));
    return &remoteOrders.back();
}

LocalOrder *Restaurant::newLocalOrder(Table *table)
{
    localOrders.push_back(LocalOrder(*table));
    return &localOrders.back();
}

void Restaurant::closeRestaurant()
{
    if (!localOrders.empty() || !remoteOrders.empty())
        throw std::runtime_error("cannot close restaurant, when some orders are still in progress");
}

void Restaurant::changeCurrentWaiter(Waiter *waiter)
{
    currentWaiter = waiter;
}

Waiter *Restaurant::getCurrentWaiter()
{
    return currentWaiter;
}

std::vector<Waiter> &Restaurant::getWaiters()
{
    return waiters;
}
std::vector<Table> &Restaurant::getTables()
{
    return tables;
}
Menu const &Restaurant::getMenu() const
{
    return menu;
}