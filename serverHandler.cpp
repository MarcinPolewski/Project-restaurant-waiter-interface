#include "serverhandler.h"
// #include "rapidcsv.h"
#include "csv.h"
// #include "build/_deps/csv-src/src/rapidcsv.h"
// #include "_deps/csv-src/src/rapidcsv.h"

ServerHandler::ServerHandler()
{
    readConfig();
    update();
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

void ServerHandler::update()
{
    updateFile(tablesPath);
    updateFile(waitersPath);
    updateFile(beveragesPath);
    updateFile(dishesPath);
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

    // read path to dishes
    confFileReader >> s;
    if (s != "dishes_local_path:")
        throw std::runtime_error("Invalid conf file structure");
    confFileReader >> dishesPath;
    if (!pathIsCorrect(dishesPath))
        throw std::runtime_error("Invalid path to menu provided");

    // read path to beverages
    confFileReader >> s;
    if (s != "beverages_local_path:")
        throw std::runtime_error("Invalid conf file structure");
    confFileReader >> beveragesPath;
    if (!pathIsCorrect(beveragesPath))
        throw std::runtime_error("Invalid path to menu provided");

    // ---------------- Reading version
    confFileReader >> s;
    if (s != "waiters_local_version:")
        throw std::runtime_error("Invalid conf file structure");
    confFileReader >> waitersLocalVersion;

    confFileReader >> s;
    if (s != "tables_local_version:")
        throw std::runtime_error("Invalid conf file structure");
    confFileReader >> tablesLocalVersion;

    confFileReader >> s;
    if (s != "dishes_local_version:")
        throw std::runtime_error("Invalid conf file structure");
    confFileReader >> dishesLocalVersion;

    confFileReader >> s;
    if (s != "beverages_local_version:")
        throw std::runtime_error("Invalid conf file structure");
    confFileReader >> beveragesLocalVersion;

    confFileReader.close();
}

void ServerHandler::fetchDishes(std::vector<std::unique_ptr<MenuItem>> &arr)
{

    io::CSVReader<6, io::trim_chars<' '>, io::double_quote_escape<',', '\"'>> in(dishesPath);
    // io::CSVReader<5> in(dishesPath);
    in.read_header(io::ignore_extra_column, "name", "description", "category", "price", "ingredients", "volume");

    std::string name;
    std::string description;
    unsigned int category;
    unsigned int price;
    std::string ingredients;
    unsigned int volume;

    while (in.read_row(name, description, category, price, ingredients, volume))
    {

        MenuItem::CATEGORY convertedCategory = static_cast<MenuItem::CATEGORY>(category);
        arr.push_back(std::make_unique<Dish>(
            name,
            description,
            convertedCategory,
            price,
            ingredients,
            volume));
    }
}

void ServerHandler::fetchBeverages(std::vector<std::unique_ptr<MenuItem>> &arr)
{
    updateFile(beveragesPath);

    io::CSVReader<6, io::trim_chars<' '>, io::double_quote_escape<',', '\"'>> in(beveragesPath);
    in.read_header(io::ignore_extra_column, "name", "description", "category", "price", "alcoholPercentage", "volume");

    std::string name;
    std::string description;
    unsigned int category;
    unsigned int price;
    unsigned int alcoholPercentage;
    unsigned int volume;

    while (in.read_row(name, description, category, price, alcoholPercentage, volume))
    {
        MenuItem::CATEGORY convertedCategory = static_cast<MenuItem::CATEGORY>(category);

        arr.push_back(std::make_unique<Beverage>(
            name,
            description,
            convertedCategory,
            price,
            alcoholPercentage,
            volume));
    }
}

Menu ServerHandler::fetchMenu()
{
    std::vector<std::unique_ptr<MenuItem>> items;
    fetchDishes(items);
    fetchBeverages(items);

    return Menu(std::move(items));
}

std::vector<Waiter> ServerHandler::fetchWaiters()
{
    updateFile(waitersPath);
}

std::vector<Table> ServerHandler::fetchTables()
{
    updateFile(tablesPath);
}

void ServerHandler::archiveOrder(const Order *order)
{
    /*
    this is only a place holder method

    normaly it would send this order to server, where it would be stored
    for statistics
    */
}

void ServerHandler::sendOrderItem(OrderItem *order)
{
    requestedOrders.push_back(order);
}