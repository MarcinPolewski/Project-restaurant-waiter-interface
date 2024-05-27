#include "memoryhandler.h"

bool MemoryHandler::pathIsCorrect(std::string &path)
{
    return std::filesystem::exists(path);
}

void MemoryHandler::readConfig()
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

void MemoryHandler::fetchDishes(std::vector<std::unique_ptr<MenuItem>> &arr)
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

void MemoryHandler::fetchBeverages(std::vector<std::unique_ptr<MenuItem>> &arr)
{

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

Menu MemoryHandler::fetchMenu()
{
    std::vector<std::unique_ptr<MenuItem>> items;
    fetchDishes(items);
    fetchBeverages(items);

    return Menu(std::move(items));
}

std::vector<Waiter> MemoryHandler::fetchWaiters()
{
    io::CSVReader<3, io::trim_chars<' '>, io::double_quote_escape<',', '\"'>> in(beveragesPath);
    in.read_header(io::ignore_extra_column, "id", "name", "surname");

    std::string name;
    std::string surname;
    unsigned int id;

    std::vector<Waiter> arr;
    while (in.read_row(id, name, surname))
    {
        arr.push_back(Waiter(id, name, surname));
    }

    return arr;
}

std::vector<Table> MemoryHandler::fetchTables()
{
    io::CSVReader<4, io::trim_chars<' '>, io::double_quote_escape<',', '\"'>> in(beveragesPath);
    in.read_header(io::ignore_extra_column, "x", "y", "level", "numerOfSeats");

    unsigned int x;
    unsigned int y;
    int level;
    unsigned int nOfSeats;

    std::vector<Table> arr;
    while (in.read_row(x, y, level, nOfSeats))
    {
        arr.push_back(Table(Table::Position(x, y, level), nOfSeats));
    }

    return arr;
}

std::string MemoryHandler::getWaitersVersion() const
{
    return waitersLocalVersion;
}
std::string MemoryHandler::getTablesVersion() const
{
    return tablesLocalVersion;
}

std::string MemoryHandler::getDishesVersion() const
{
    return dishesLocalVersion;
}
std::string MemoryHandler::getBeveragesVersion() const
{
    return beveragesLocalVersion;
}

void MemoryHandler::setWaitersVersion(const std::string &version)
{
    waitersLocalVersion = version;
}
void MemoryHandler::setTablesVersion(const std::string &version)
{
    tablesLocalVersion = version;
}
void MemoryHandler::setDishesVersion(const std::string &version)
{
    dishesLocalVersion = version;
}
void MemoryHandler::setBeveragesVersion(const std::string &version)
{
    beveragesLocalVersion = version;
}
