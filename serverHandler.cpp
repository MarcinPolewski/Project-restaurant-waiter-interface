#include "serverHandler.h"

ServerHandler::ServerHandler()
{
    readConfig();
}

bool ServerHandler::pathIsCorrect(std::string &path)
{
    return std::filesystem::exists(path);
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

std::vector<Waiter> ServerHandler::fetchWaiters()
{
    // 1. check if downloaded version of waiters is up to date
    // 2. if not, download new version
    // 3. read waiters (if error encountered, download file and try again, if not print message)
    // 4. return them
}

std::vector<Table> ServerHandler::fetchTables()
{
    // 1. check if downloaded version of tables is up to date
    // 2. if not, download new version
    // 3. read tables
    // 4. return them
}