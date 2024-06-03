#pragma once

#include "serverhandler.h"
#include "memoryhandler.h"
#include "waiter.h"
#include "destination.h"

#include <stdexcept>

class Restaurant
{
    MemoryHandler memoryHandler;
    ServerHandler serverHandler;
    Menu menu;
    const std::vector<Waiter> waiters;
    const std::vector<Table> tables;

    std::vector<std::unique_ptr<LocalOrder>> localOrders;
    std::vector<RemoteOrder> remoteOrders;

    const Waiter *currentWaiter;

public:
    Restaurant();
    void closeRestaurant();

    void changeCurrentWaiter(Waiter *waiter);
    Waiter const *getCurrentWaiter() const;

    RemoteOrder *newRemoteOrder(Remote *remote);
    LocalOrder& newLocalOrder(Table& table);

    std::vector<Waiter> const &getWaiters() const;
    std::vector<Table> const &getTables() const;
    Menu const &getMenu() const;
};