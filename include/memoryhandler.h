#pragma once

#include <vector>
#include <string>
#include <filesystem>
#include <fstream>

#include "waiter.h"
#include "destination.h"
#include "menu.h"
#include "order.h"

#include "csv.h"

class MemoryHandlerInterface
{
public:
    virtual Menu fetchMenu() = 0;
    virtual std::vector<Waiter> fetchWaiters() = 0;
    virtual std::vector<Table> fetchTables() = 0;

    virtual std::string getWaitersVersion() const = 0;
    virtual std::string getTablesVersion() const = 0;
    virtual std::string getDishesVersion() const = 0;
    virtual std::string getBeveragesVersion() const = 0;

    virtual std::string getWaitersPath() const = 0;
    virtual std::string getTablesPath() const = 0;
    virtual std::string getDishesPath() const = 0;
    virtual std::string getBeveragesPath() const = 0;

    virtual void setWaitersVersion(const std::string &version) = 0;
    virtual void setTablesVersion(const std::string &version) = 0;
    virtual void setBeveragesVersion(const std::string &version) = 0;
    virtual void setDishesVersion(const std::string &version) = 0;
};

class MemoryHandler : MemoryHandlerInterface
{
    std::string configPath = "/Users/marcinpolewski/Documents/Studia/SEM2/PROI/restaurant/serverHandlerConf/conf.txt"; // configuration file for behaviour of handler

    // paths to files
    std::string dishesPath;
    std::string beveragesPath;
    std::string waitersPath;
    std::string tablesPath;

    // versions of files
    std::string dishesLocalVersion;
    std::string beveragesLocalVersion;
    std::string waitersLocalVersion;
    std::string tablesLocalVersion;

    bool pathIsCorrect(std::string &path); // check if provided path is ok

    void fetchDishes(std::vector<std::unique_ptr<MenuItem>> &arr);
    void fetchBeverages(std::vector<std::unique_ptr<MenuItem>> &arr);

    void readConfig();

public:
    MemoryHandler();
    Menu fetchMenu() override;
    std::vector<Waiter> fetchWaiters() override;
    std::vector<Table> fetchTables() override;

    std::string getWaitersVersion() const override;
    std::string getTablesVersion() const override;
    std::string getDishesVersion() const override;
    std::string getBeveragesVersion() const override;

    virtual std::string getWaitersPath() const override;
    virtual std::string getTablesPath() const override;
    virtual std::string getDishesPath() const override;
    virtual std::string getBeveragesPath() const override;

    void setWaitersVersion(const std::string &version) override;
    void setTablesVersion(const std::string &version) override;
    void setDishesVersion(const std::string &version) override;
    void setBeveragesVersion(const std::string &version) override;
};