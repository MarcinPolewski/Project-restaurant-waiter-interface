#pragma once

#include "serverhandler.h"
#include "memoryhandler.h"
#include "waiter.h"
#include "filtered_unique_iterator.h"

#include <stdexcept>

class Restaurant
{
    MemoryHandler memoryHandler;
    ServerHandler serverHandler;
    Menu menu;

    std::vector<std::unique_ptr<Waiter>> waiters;

    const std::vector<Table> tables;

    std::vector<std::unique_ptr<Order>> orders;

public:
    Restaurant();
    void closeRestaurant();

    RemoteOrder& newRemoteOrder(Waiter& waiter, Remote& remote);
    LocalOrder& newLocalOrder(Waiter& waiter,Table& table);

    typedef filtered_unique_iterator<Waiter> WTiterator;
    WTiterator wtbegin();
    WTiterator wtend();

    std::vector<Table> const &getTables() const;
    Menu const &getMenu() const;

    class LOiterator : public filtered_unique_iterator<Order>
    {
    public:
        using filtered_unique_iterator::filtered_unique_iterator;
        LOiterator& operator++();
        LocalOrder& operator*();
    };
    LOiterator lobegin();
    LOiterator loend();

    class RTiterator : public filtered_unique_iterator<Order>
    {
    public:
        using filtered_unique_iterator::filtered_unique_iterator;
        RTiterator& operator++();
        RemoteOrder& operator*();
    };
    RTiterator rtbegin();
    RTiterator rtend();
};