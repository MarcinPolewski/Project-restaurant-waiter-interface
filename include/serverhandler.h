#pragma once

#include "menu.h"
#include "waiter.h"
#include "destination.h"
#include "order.h"
#include "orderitem.h"
#include "memoryhandler.h"

#include <string>

class ServerHandlerInterface
{
public:
    virtual void archiveOrder(const Order *order) = 0;
    virtual void sendOrderItem(OrderItem *order) = 0;
    virtual ~ServerHandlerInterface() = default;
};

class ServerHandler : public ServerHandlerInterface
{

    std::vector<OrderItem *> requestedOrders;

    // void updateFile(const std::string &pathToLocal); // check if file is up to date

public:
    ServerHandler(MemoryHandler &memoryHandler)
    {
        updateFile(memoryHandler.getWaitersPath(), memoryHandler.getWaitersVersion());
        updateFile(memoryHandler.getTablesPath(), memoryHandler.getTablesVersion());
        updateFile(memoryHandler.getDishesPath(), memoryHandler.getDishesVersion());
        updateFile(memoryHandler.getBeveragesPath(), memoryHandler.getBeveragesVersion());
    }

    std::string updateFile(const std::string, const std::string)
    {
        return "1.1.0";
    }
    void archiveOrder(const Order*) override
    {
    }
    void sendOrderItem(OrderItem*) override // sends this message to server
    {
        requestedOrders.push_back(order);
    }
};