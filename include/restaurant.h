#pragma once

#include "serverhandler.h"
#include "memoryhandler.h"
#include "waiter.h"
#include "filtered_unique_iterator.h"

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
protected:
    MemoryHandler memoryHandler;
    ServerHandler serverHandler;
    Menu menu;

    std::vector<std::unique_ptr<Waiter>> waiters;
    std::vector<std::unique_ptr<Table>> tables;
    std::vector<std::unique_ptr<Order>> orders;

public:
    Restaurant();

    const Menu &getMenu() const;

    typedef filtered_unique_iterator<Waiter> WTiterator;
    WTiterator wtbegin();
    WTiterator wtend();

    typedef filtered_unique_iterator<Table> TBiterator;
    TBiterator tbbegin();
    TBiterator tbend();

    RemoteOrder &newRemoteOrder(Waiter &waiter, Remote &remote);
    LocalOrder &newLocalOrder(Waiter &waiter, Table &table);

    class LOiterator : public filtered_unique_iterator<Order>
    {
    public:
        using filtered_unique_iterator::filtered_unique_iterator;
        LOiterator &operator++();
        LocalOrder &operator*();
    };
    LOiterator lobegin();
    LOiterator loend();

    LOiterator lobegin_inprogress();

    class RTiterator : public filtered_unique_iterator<Order>
    {
    public:
        using filtered_unique_iterator::filtered_unique_iterator;
        RTiterator &operator++();
        RemoteOrder &operator*();
    };
    RTiterator rtbegin();
    RTiterator rtend();

    RTiterator rtbegin_inprogress();

    unsigned int openLocalOrdersCount();
    unsigned int openRemoteOrdersCount();

    bool canBeClosed();
    void close();
    bool isClosed()
    {
        return false;
    }
};

class UIRestaurant : public Restaurant
{
    Waiter *currentWaiter;

public:
    UIRestaurant()
        : Restaurant()
    {
        currentWaiter = (waiters[0]).get();
    }

    RemoteOrder &newRemoteOrder(Remote &remote)
    {
        return Restaurant::newRemoteOrder(*currentWaiter, remote);
    }
    LocalOrder &newLocalOrder(Table &table)
    {
        return Restaurant::newLocalOrder(*currentWaiter, table);
    }

    Waiter *getCurrentWaiter()
    {
        return currentWaiter;
    }
    void changeCurrentWaiter(Waiter *newWaiter)
    {
        currentWaiter = newWaiter;
    }
};
