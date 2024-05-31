#pragma once

#include "orderitem.h"
#include "destination.h"

#include <time.h>
#include <vector>

class Waiter;

enum class OrderStatus
{
    inProgress,
    closed,
    canceled
};

class WaiterOrder
{
    virtual WaiterOrderItem& addOrderItem(const MenuItem& menu_item, unsigned int count,
        const std::string& com = "", unsigned int discnt = 0) = 0;
    virtual WaiterOrderItem& getOrderItem(unsigned int index) = 0;
    // virtual void removeOrderItem(unsigned int index) = 0;
    virtual const Destination& getDestination() const = 0;
    virtual OrderStatus getStatus() const = 0;
    // virtual void setClosed() = 0;
    // virtual void setCanceled() = 0;
    virtual time_t getOrderTime() const = 0;
    virtual time_t getWaitingTime() const = 0;
    virtual void resetWaitingTime() = 0;
    virtual unsigned int getTotalPrice() const = 0;
};

// iterator i const_iterator
// destination

class Order : WaiterOrder
{
private:
    OrderStatus orderStatus = OrderStatus::inProgress;
    time_t waitingTimeStamp = time(NULL);
    std::vector<OrderItem> orderItems;
public:
    const time_t orderTime = this->waitingTimeStamp;

    virtual ~Order() = default;

    OrderItem& addOrderItem(const MenuItem& menu_item, unsigned int count,
        const std::string& com = "", unsigned int discnt = 0) override;

    OrderItem& getOrderItem(unsigned int index) override;

    virtual const Destination& getDestination() const override = 0;

    OrderStatus getStatus() const override {return orderStatus;}

    time_t getOrderTime() const override {return this->orderTime;}
    time_t getWaitingTime() const override {return time(NULL) - this->waitingTimeStamp;}
    void resetWaitingTime() override {this->waitingTimeStamp = time(NULL);}

    unsigned int getTotalPrice() const override;
};

class LocalOrder : public Order
{
public:
    const Table& table;

    LocalOrder(Table& tbl)
        : table(tbl) {}

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