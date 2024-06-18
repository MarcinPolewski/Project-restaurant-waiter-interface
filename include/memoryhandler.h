/*
 * Copyright (c) 2015, ben-strasser
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of fast-cpp-csv-parser nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

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
    std::string configFilePath;
    std::string configFolderPath;

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

    bool pathIsCorrect(const std::string &path); // check if provided path is ok

    void fetchDishes(std::vector<std::unique_ptr<MenuItem>> &arr);
    void fetchBeverages(std::vector<std::unique_ptr<MenuItem>> &arr);

    void readConfig();

public:
    MemoryHandler(const std::string &configFolderName = "memoryHandlerConf");
    Menu fetchMenu() override;
    std::vector<Waiter> fetchWaiters() override;
    std::vector<Table> fetchTables() override;

    std::string getWaitersVersion() const override;
    std::string getTablesVersion() const override;
    std::string getDishesVersion() const override;
    std::string getBeveragesVersion() const override;

    std::string getWaitersPath() const override;
    std::string getTablesPath() const override;
    std::string getDishesPath() const override;
    std::string getBeveragesPath() const override;

    void setWaitersVersion(const std::string &version) override;
    void setTablesVersion(const std::string &version) override;
    void setDishesVersion(const std::string &version) override;
    void setBeveragesVersion(const std::string &version) override;
};