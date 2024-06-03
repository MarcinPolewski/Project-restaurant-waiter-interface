#pragma once

#include "serverhandler.h"
#include "memoryhandler.h"
#include "waiter.h"

#include "topbar.h"
#include "mainscreen.h"
#include "popuphandler.h"
#include "consoleuiobject.h"
#include "constants.h"
#include "menuitem.h"
#include "popupmenu.h"

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
    Waiter *getCurrentWaiter();

    RemoteOrder *newRemoteOrder(Remote *remote);
    LocalOrder *newLocalOrder(Table *table);

    std::vector<Waiter> &getWaiters();
    std::vector<Table> &getTables();
    Menu const &getMenu() const;
};