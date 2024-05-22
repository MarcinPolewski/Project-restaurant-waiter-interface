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

Menu ServerHandler::fetchMenu()
{
    updateFile(menuPath);

    std::ifstream menuReader(menuPath);
    if (!menuReader.good())
        throw std::runtime_error("Could not open file with menu");

    Menu menu;
    menuReader >> menu;

    menuReader.close();
    return menu;
}

std::vector<Waiter> ServerHandler::fetchWaiters()
{
    updateFile(waitersPath);

    std::ifstream waitersReader(waitersPath);
    if (!waitersReader.good())
        throw std::runtime_error("Could not open file with waiters");

    std::vector<Waiter> waiters;
    Waiter waiter;
    while (waitersReader >> waiter)
        waiters.push_back(waiter);

    waitersReader.close();
    return waiters;
}

std::vector<Table> ServerHandler::fetchTables()
{
    updateFile(tablesPath);

    std::ifstream tablesReader(tablesPath);
    if (!tablesReader.good())
        throw std::runtime_error("Could not open file with waiters");

    std::vector<Table> tables;
    Table table;
    while (tablesReader >> table)
        tables.push_back(table);

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