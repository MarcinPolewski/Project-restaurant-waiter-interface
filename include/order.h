#pragma once

#include "orderitem.h"
#include "table.h"
#include "remote.h"
#include "filtered_unique_iterator.h"

#include <time.h>
#include <vector>

enum class OrderStatus
{
    inProgress,
    closed
};

class Order
{
private:
    std::vector<std::unique_ptr<OrderItem>> orderItems;
    OrderStatus orderStatus = OrderStatus::inProgress;
    const time_t orderTime = time(NULL);
    time_t waitingTimeStamp = this-> orderTime;

public:
    virtual ~Order() = default;

    void addOrderItem(const MenuItem& menu_item, unsigned int count,
        const std::string& com = "", unsigned int discnt = 0);

    OrderItem& operator[](unsigned int index);

    virtual const Destination& getDestination() const = 0;

    OrderStatus getStatus() const;
    virtual void setClosed();

    time_t getOrderTime() const;
    time_t getWaitingTime() const;
    void resetWaitingTime();

    unsigned int getTotalPrice() const;

    typedef filtered_unique_iterator<OrderItem> OIiterator;
    OIiterator oibegin();
    OIiterator oiend();
};

class LocalOrder : public Order
{
public:
    const Table& table;

    LocalOrder(Table& tbl);

    void setClosed() override;

    const Table& getDestination() const override {return table;}
};

class RemoteOrder : public Order
{
public:
    const Remote remote;

    RemoteOrder(const Remote& rmt)
        : remote(rmt) {}

    const Remote& getDestination() const override {return remote;}
};