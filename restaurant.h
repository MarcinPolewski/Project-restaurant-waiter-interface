#pragma once

#include "serverhandler.h"

#include <stdexcept>

class Restaurant
{
    ServerHandler serverHandler;
    Menu menu;
    std::vector<Waiter> waiters;
    std::vector<Table> tables;

    Waiter *currentWaiter;

public:
    Restaurant();
    void closeRestaurant(); // returns true if operation successful

    void changeCurrentWaiter(Waiter *waiter);
    Waiter const *getCurrentWaiter();

    std::vector<Waiter> const &getWaiters();
    std::vector<Table> const &getTables();
    Menu const &getMenu();
};