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

    std::vector<std::unique_ptr<Order>> orders;

    Waiter *currentWaiter;
    bool closed = false;

    typedef std::vector<std::unique_ptr<Order>>::iterator u_order_iterator;

public:
    Restaurant();
    void closeRestaurant();

    void changeCurrentWaiter(Waiter *waiter);
    Waiter *getCurrentWaiter();

    int remoteOrdersCount();
    int localOrdersCount();

    RemoteOrder &newRemoteOrder(Remote &remote);
    LocalOrder &newLocalOrder(Table &table);

    std::vector<Waiter> &getWaiters();
    std::vector<Table> &getTables();
    Menu const &getMenu() const;

    bool canBeClosed();
    bool isClosed();
    void close();
    class LOiterator
    {
    private:
        u_order_iterator current_it;
        u_order_iterator end_it;

        LOiterator(u_order_iterator start_it, u_order_iterator end_it);

        friend class Restaurant;

    public:
        LOiterator &operator++();
        LocalOrder &operator*();
        bool operator!=(const LOiterator &it2) const;
    };
    LOiterator lobegin();
    LOiterator loend();

    class RTiterator
    {
    private:
        u_order_iterator current_it;
        u_order_iterator end_it;

        RTiterator(u_order_iterator start_it, u_order_iterator end_it);

        friend class Restaurant;

    public:
        RTiterator &operator++();
        RemoteOrder &operator*();
        bool operator!=(const RTiterator &it2) const;
    };
    RTiterator rtbegin();
    RTiterator rtend();
};