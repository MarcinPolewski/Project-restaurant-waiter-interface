#pragma once

#include "menu.h"
#include "waiter.h"
#include "destination.h"
#include "order.h"

#include <fstream>
#include <string>
#include <filesystem>

class ServerHandler
{
    const char separator = '|';

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
    Menu fetchMenu();
    std::vector<Waiter> fetchWaiters();
    std::vector<Table> fetchTables();
    void archiveOrder(const Order *order);
};