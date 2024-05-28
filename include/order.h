#pragma once

#include "orderitem.h"
#include "destination.h"

#include <time.h>
#include <vector>

enum class OrderStatus
{
    inPreparation,
    readyToDeliver,
    delivered,
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
    // virtual time_t getWaitingTime() = 0;
    // virtual void resetWaitingTime() = 0;
    virtual unsigned int getTotalPrice() const = 0;
    // virtual std::string& getRecipt() = 0;
};

class Order : WaiterOrder
{
private:
    OrderStatus orderStatus = OrderStatus::inPreparation;
    time_t waitingTimeStamp = time(NULL);
    std::vector<OrderItem> orderItems;
public:
    const time_t orderTime = this->waitingTimeStamp;

    virtual ~Order() = default;

    OrderItem& addOrderItem(const MenuItem& menu_item, unsigned int count,
        const std::string& com = "", unsigned int discnt = 0) override;

    OrderItem& getOrderItem(unsigned int index) override;

    time_t getOrderTime() const override {return this->orderTime;}

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