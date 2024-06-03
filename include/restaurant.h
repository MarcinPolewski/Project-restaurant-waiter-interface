#pragma once

#include "serverhandler.h"
#include "memoryhandler.h"
#include "waiter.h"

#include <stdexcept>

class Restaurant
{
    MemoryHandler memoryHandler;
    ServerHandler serverHandler;
    Menu menu;
    std::vector<Waiter> waiters;
    std::vector<Table> tables;

    std::vector<std::unique_ptr<LocalOrder>> localOrders;
    std::vector<std::unique_ptr<RemoteOrder>> remoteOrders;

    Waiter *currentWaiter;
public:
    Restaurant();
    void closeRestaurant();

    void changeCurrentWaiter(Waiter *waiter);
    Waiter const *getCurrentWaiter() const;

    RemoteOrder& newRemoteOrder(Remote& remote);
    LocalOrder& newLocalOrder(Table& table);

    std::vector<Waiter> const &getWaiters() const;
    std::vector<Table> const &getTables() const;
    Menu const &getMenu() const;
};