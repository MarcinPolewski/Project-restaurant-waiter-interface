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

    std::vector<LocalOrder> localOrders;
    std::vector<RemoteOrder> remoteOrders;

    Waiter *currentWaiter;

public:
    Restaurant();
    void closeRestaurant();

    void changeCurrentWaiter(Waiter *waiter);
    Waiter const *getCurrentWaiter();

    RemoteOrder *newRemoteOrder(Destination *destination);
    LocalOrder *newLocalOrder(Table *table);

    std::vector<Waiter> const &getWaiters();
    std::vector<Table> const &getTables();
    Menu const &getMenu();
};