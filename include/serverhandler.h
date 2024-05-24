#pragma once

#include "menu.h"
#include "waiter.h"
#include "destination.h"
#include "order.h"
#include "orderitem.h"

#include <fstream>
#include <string>
#include <filesystem>

class ServerHandlerInterface
{
public:
    virtual Menu fetchMenu() = 0;
    virtual std::vector<Waiter> fetchWaiters() = 0;
    virtual std::vector<Table> fetchTables() = 0;
    virtual void archiveOrder(const Order *order) = 0;
    virtual void sendOrderItem(OrderItem *order) = 0;
};

class ServerHandler : public ServerHandlerInterface
{

    std::vector<OrderItem *> requestedOrders;

    std::string configPath = "/Users/marcinpolewski/Documents/Studia/SEM2/PROI/restaurant/serverHandlerConf/conf.txt"; // configuration file for behaviour of handler

    std::string dishesPath;
    std::string beveragesPath;
    std::string waitersPath;
    std::string tablesPath;

    std::string dishesLocalVersion;
    std::string beveragesLocalVersion;
    std::string waitersLocalVersion;
    std::string tablesLocalVersion;

    bool pathIsCorrect(std::string &path);           // check if provided path is ok
    void updateFile(const std::string &pathToLocal); // check if file is up to date
    void update();
    void readConfig();

    void fetchDishes(std::vector<std::unique_ptr<MenuItem>> &arr);
    void fetchBeverages(std::vector<std::unique_ptr<MenuItem>> &arr);

public:
    ServerHandler();
    Menu fetchMenu() override;
    std::vector<Waiter> fetchWaiters() override;
    std::vector<Table> fetchTables() override;
    void archiveOrder(const Order *order) override;
    void sendOrderItem(OrderItem *order) override; // sends this message to server
};