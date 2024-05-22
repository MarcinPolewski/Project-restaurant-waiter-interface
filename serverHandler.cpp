#include "serverHandler.h"

ServerHandler::ServerHandler()
{
    readConfig();
}

bool ServerHandler::pathIsCorrect(std::string &path)
{
    return std::filesystem::exists(path);
}

void ServerHandler::updateFile(const std::string &pathToLocal)
{
    /*
    this method is only a place holder, for sake of this project we will
    not create a server.

    This method would send request to server, that would compare versions of files.
    If local version was outdated, new version would be downloaded.
    */
}

void ServerHandler::readConfig()
{
    std::ifstream confFileReader(configPath);
    // auto pwd = std::filesystem::current_path();

    if (!confFileReader.good())
    {
        throw std::runtime_error("could not open config file to read");
    }

    std::string s;

    // read path to waiters
    confFileReader >> s;
    if (s != "waiters_local_path:")
        throw std::runtime_error("Invalid conf file structure");
    confFileReader >> waitersPath;
    if (!pathIsCorrect(waitersPath))
        throw std::runtime_error("Invalid path to waiters provided");

    // read path to tables
    confFileReader >> s;
    if (s != "tables_local_path:")
        throw std::runtime_error("Invalid conf file structure");
    confFileReader >> tablesPath;
    if (!pathIsCorrect(tablesPath))
        throw std::runtime_error("Invalid path to tables provided");

    // read path to menu
    confFileReader >> s;
    if (s != "menu_local_path:")
        throw std::runtime_error("Invalid conf file structure");
    confFileReader >> menuPath;
    if (!pathIsCorrect(menuPath))
        throw std::runtime_error("Invalid path to menu provided");

    confFileReader.close();
}

std::unique_ptr<Dish> ServerHandler::readDish(std::istream &stream)
{
    char c;
    stream >> c;
    if (c != '{')
        throw std::runtime_error("Invalid dish structure provided");

    std::string name;
    std::string description;
    std::string ingredients;
    unsigned int price, volume;

    stream >> name >> description >> price >> ingredients >> volume;

    stream >> c;
    if (c != '}')
        throw std::runtime_error("Invalid dish structure provided");
    return std::make_unique<Dish>(name, description, price, ingredients, volume);
}

//     Beverage(const std::string &name, const std::string &description, unsigned int price, unsigned int alcoholPercentage, unsigned int volume)
std::unique_ptr<Beverage> ServerHandler::readBeverage(std::istream &stream)
{
    char c;
    stream >> c;
    if (c != '{')
        throw std::runtime_error("Invalid dish structure provided");

    std::string name;
    std::string description;
    unsigned int price, volume, alcoholPercentage;

    stream >> name >> description >> price >> alcoholPercentage >> volume;

    stream >> c;
    if (c != '}')
        throw std::runtime_error("Invalid dish structure provided");
    return std::make_unique<Beverage>(name, description, price, alcoholPercentage, volume);
}

Menu ServerHandler::fetchMenu()
{
    updateFile(menuPath);

    std::ifstream menuReader(menuPath);
    if (!menuReader.good())
        throw std::runtime_error("Could not open file with menu");

    // read version
    std::string version;
    menuReader >> version;

    std::vector<std::unique_ptr<MenuItem>> items;

    std::string classType;
    while (!menuReader.eof())
    {
        menuReader >> classType;
        if (classType == "Dish")
            items.push_back(readDish(menuReader));
        else
            items.push_back(readBeverage(menuReader));
    }

    // read items

    menuReader.close();
    return Menu(std::move(items));
}

std::vector<Waiter> ServerHandler::fetchWaiters()
{
    updateFile(waitersPath);

    std::ifstream waitersReader(waitersPath);
    if (!waitersReader.good())
        throw std::runtime_error("Could not open file with waiters");

    // read version
    std::string version;
    waitersReader >> version;

    std::vector<Waiter> waiters;
    while (waitersReader.eof())
        waiters.push_back(readWaiter(waitersReader));

    waitersReader.close();
    return waiters;
}

std::vector<Table> ServerHandler::fetchTables()
{
    updateFile(tablesPath);

    std::ifstream tablesReader(tablesPath);
    if (!tablesReader.good())
        throw std::runtime_error("Could not open file with waiters");

    // read version
    std::string version;
    tablesReader >> version;

    std::vector<Table> tables;
    while (tablesReader.eof())
        tables.push_back(readTable(tablesReader));

    tablesReader.close();
    return tables;
}

void archiveOrder(const Order *order)
{
    /*
    this is only a place holder method

    normaly it would send this order to server, where it would be stored
    for statistics
    */
}