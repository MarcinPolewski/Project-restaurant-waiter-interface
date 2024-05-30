#pragma once

#include "orderitem.h"
#include "destination.h"

#include <time.h>
#include <vector>

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
    // virtual Destination& getDestination() = 0;
    // virtual OrderStatus getStatus() = 0;
    virtual time_t getOrderTime() const = 0;
    virtual time_t getWaitingTime() const = 0;
    virtual void resetWaitingTime() = 0;
    virtual unsigned int getTotalPrice() const = 0;
    // virtual std::string& getRecipt() = 0;
};

// iterator i const_iterator
// Waiter constr
// destination

class Order : WaiterOrder
{
private:
    OrderStatus orderStatus = OrderStatus::inProgress;
    time_t waitingTimeStamp = time(NULL);
    std::vector<OrderItem> orderItems;
public:
    const time_t orderTime = this->waitingTimeStamp;

    // Order(Waiter waiter);

    virtual ~Order() = default;

    OrderItem& addOrderItem(const MenuItem& menu_item, unsigned int count,
        const std::string& com = "", unsigned int discnt = 0) override;

    OrderItem& getOrderItem(unsigned int index) override;

    time_t getOrderTime() const override {return this->orderTime;}
    time_t getWaitingTime() const override {return time(NULL) - this->waitingTimeStamp;}
    void resetWaitingTime() override {this->waitingTimeStamp = time(NULL);}

    unsigned int getTotalPrice() const override;
    virtual void nothing() = 0;
};

class LocalOrder : public Order
{
    void nothing() override {}
};

class RemoteOrder : public Order
{
    void nothing() override {}
};