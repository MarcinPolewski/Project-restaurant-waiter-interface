#pragma once

#include "orderitem.h"
#include "table.h"
#include "remote.h"

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
    OrderStatus orderStatus = OrderStatus::inProgress;
    time_t waitingTimeStamp = time(NULL);
    std::vector<std::unique_ptr<OrderItem>> orderItems;
public:
    const time_t orderTime = this->waitingTimeStamp;

    virtual ~Order() = default;

    void addOrderItem(const MenuItem& menu_item, unsigned int count,
        const std::string& com = "", unsigned int discnt = 0);

    OrderItem& operator[](unsigned int index);

    virtual const Destination& getDestination() const = 0;

    OrderStatus getStatus() const {return orderStatus;}
    virtual void setClosed();

    time_t getOrderTime() const {return this->orderTime;}
    time_t getWaitingTime() const;
    void resetWaitingTime();

    unsigned int getTotalPrice() const;

    class iterator
    {
    private:
        std::vector<std::unique_ptr<OrderItem>>::iterator it;

        iterator(std::vector<std::unique_ptr<OrderItem>>::iterator iter)
            : it(iter) {}

        friend class Order;
    public:
        iterator& operator++();
        OrderItem& operator*() {return *it->get();}
        bool operator!=(iterator it2) const {return this->it != it2.it;}
    };
    iterator begin() {return iterator(orderItems.begin());}
    iterator end() {return iterator(orderItems.end());}

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