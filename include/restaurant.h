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
    const std::vector<Waiter> waiters;
    const std::vector<Table> tables;

    std::vector<std::unique_ptr<Order>> orders;

    const Waiter *currentWaiter;

    typedef std::vector<std::unique_ptr<Order>>::iterator u_order_iterator;
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

    class LOiterator
    {
    private:
        u_order_iterator current_it;
        u_order_iterator end_it;

        LOiterator(u_order_iterator start_it, u_order_iterator end_it);

        friend class Restaurant;
    public:
        LOiterator& operator++();
        LocalOrder& operator*();
        bool operator!=(const LOiterator& it2) const;
    };

    LOiterator lobegin();
    LOiterator loend();
};