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
    std::vector<std::unique_ptr<Table>> tables;
    std::vector<std::unique_ptr<Order>> orders;

    bool isWaiter(Waiter& waiter);
public:
    Restaurant();

    const Menu &getMenu() const;

    typedef filtered_unique_iterator<Waiter> WTiterator;
    WTiterator wtbegin();
    WTiterator wtend();

    typedef filtered_unique_iterator<Table> TBiterator;
    TBiterator tbbegin();
    TBiterator tbend();

    LocalOrder& newLocalOrder(Waiter& waiter,Table& table);
    RemoteOrder& newRemoteOrder(Waiter& waiter, Remote& remote);

    class LOiterator : public filtered_unique_iterator<Order>
    {
    public:
        using filtered_unique_iterator::filtered_unique_iterator;
        LOiterator& operator++();
        LocalOrder& operator*();
    };
    LOiterator lobegin();
    LOiterator loend();

    LOiterator lobegin_inprogress();

    class RTiterator : public filtered_unique_iterator<Order>
    {
    public:
        using filtered_unique_iterator::filtered_unique_iterator;
        RTiterator& operator++();
        RemoteOrder& operator*();
    };
    RTiterator rtbegin();
    RTiterator rtend();

    RTiterator rtbegin_inprogress();

    unsigned int openLocalOrdersCount();
    unsigned int openRemoteOrdersCount();

    bool canBeClosed();
    void close();
};