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

    bool isWaiter(Waiter const &waiter) const;
    bool isTable(Table const &waiter) const;

    bool isRestaurantClosed = false;

public:
    Restaurant(const std::string &configFolderName = "memoryHandlerConf");

    const Menu &getMenu() const;

    typedef filtered_unique_iterator<Waiter> WTiterator;
    WTiterator wtbegin();
    WTiterator wtend();

    typedef const_filtered_unique_iterator<Waiter> const_WTiterator;
    const_WTiterator wtcbegin() const;
    const_WTiterator wtcend() const;

    typedef filtered_unique_iterator<Table> TBiterator;
    TBiterator tbbegin();
    TBiterator tbend();

    typedef const_filtered_unique_iterator<Table> const_TBiterator;
    const_TBiterator tbcbegin() const;
    const_TBiterator tbcend() const;

    LocalOrder &newLocalOrder(Waiter &waiter, Table &table);
    RemoteOrder &newRemoteOrder(Waiter &waiter, Remote &remote);

    class LOiterator : public filtered_unique_iterator<Order>
    {
    public:
        using filtered_unique_iterator::filtered_unique_iterator;
        LOiterator &operator++();
        LocalOrder &operator*() const;
    };
    LOiterator lobegin();
    LOiterator loend();

    LOiterator lobegin_inprogress();

    class const_LOiterator : public const_filtered_unique_iterator<Order>
    {
    public:
        using const_filtered_unique_iterator::const_filtered_unique_iterator;
        const_LOiterator &operator++();
        const LocalOrder &operator*() const;
    };
    const_LOiterator locbegin() const;
    const_LOiterator locend() const;

    const_LOiterator locbegin_inprogress() const;

    class RTiterator : public filtered_unique_iterator<Order>
    {
    public:
        using filtered_unique_iterator::filtered_unique_iterator;
        RTiterator &operator++();
        RemoteOrder &operator*() const;
    };
    RTiterator rtbegin();
    RTiterator rtend();

    RTiterator rtbegin_inprogress();

    class const_RTiterator : public const_filtered_unique_iterator<Order>
    {
    public:
        using const_filtered_unique_iterator::const_filtered_unique_iterator;
        const_RTiterator &operator++();
        const RemoteOrder &operator*() const;
    };
    const_RTiterator rtcbegin() const;
    const_RTiterator rtcend() const;

    const_RTiterator rtcbegin_inprogress() const;

    unsigned int openLocalOrdersCount() const;
    unsigned int openRemoteOrdersCount() const;

    bool canBeClosed() const;
    void close();
    bool isClosed();
};

class UIRestaurant : public Restaurant
{
    Waiter *currentWaiter;

public:
    UIRestaurant();
    RemoteOrder &newRemoteOrder(Remote &remote);
    LocalOrder &newLocalOrder(Table &table);

    Waiter *getCurrentWaiter();
    void changeCurrentWaiter(Waiter *newWaiter);
};
