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
    std::string configPath = "/Users/marcinpolewski/Documents/Studia/SEM2/PROI/restaurant/serverHandlerConf/conf.txt"; // configuration file for behaviour of handler

    std::string menuPath;
    std::string waitersPath;
    std::string tablesPath;

    bool pathIsCorrect(std::string &path);           // check if provided path is ok
    void updateFile(const std::string &pathToLocal); // check if file is up to date
    void readConfig();

    std::unique_ptr<Dish> readDish(std::istream &stream);         // reads dish from stream
    std::unique_ptr<Beverage> readBeverage(std::istream &stream); // reads Beverage from stream
    Table readTable(std::istream &stream);
    Waiter readWaiter(std::istream &stream);

public:
    ServerHandler();
    Menu fetchMenu();
    std::vector<Waiter> fetchWaiters();
    std::vector<Table> fetchTables();
    void archiveOrder(const Order *order);
};