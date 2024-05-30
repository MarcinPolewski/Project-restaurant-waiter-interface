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

RemoteOrder *Restaurant::newRemoteOrder(Destination *destination)
{
    remoteOrders.push_back(RemoteOrder());
    return &remoteOrders.back();
}

LocalOrder *Restaurant::newLocalOrder(Table *table)
{
    localOrders.push_back(LocalOrder());
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