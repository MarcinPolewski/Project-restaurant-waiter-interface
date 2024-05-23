#include <gtest/gtest.h>
#include "address.h"
#include "destination.h"
#include "menuItem.h"
#include "menu.h"
#include "serverHandler.h"

TEST(AddressTest, create_typical)
{
    Address adr("Olsztyn", "10-555", "Baltycka", "4");
    ASSERT_EQ(adr.str(), "Baltycka 4\n10-555 Olsztyn");
}

TEST(AddressTest, create_with_additional_info)
{
    Address adr("Olsztyn", "10-555", "Baltycka", "4", "Klatka H6");
    ASSERT_EQ(adr.str(), "Baltycka 4\n10-555 Olsztyn\nAI: Klatka H6");
}

TEST(TableTest, create_typical)
{
    Table tbl(Table::Position(3, 5, 0), 4);
    ASSERT_EQ(tbl.position.x, 3);
    ASSERT_EQ(tbl.position.y, 5);
    ASSERT_EQ(tbl.position.level, 0);
    ASSERT_EQ(tbl.seats, 4);
    ASSERT_EQ(tbl.occupied, false);
}

TEST(TableTest, occupy)
{
    Table tbl(Table::Position(3, 5, 0), 4);
    ASSERT_EQ(tbl.occupied, false);
    tbl.occupied = true;
    ASSERT_EQ(tbl.occupied, true);
}

TEST(RemoteTest, typical)
{
    Address adr("Olsztyn", "10-555", "Baltycka", "4", "Klatka H6");
    Remote remote(adr);
    ASSERT_EQ(remote.address.city, "Olsztyn");
}

TEST(DestinationTest, cast_table)
{
    Table tbl(Table::Position(3, 5, 0), 4);
    Destination &dst = tbl;
    ASSERT_EQ(typeid(dst), typeid(tbl));
    ASSERT_EQ(dynamic_cast<Table &>(dst).position.x, 3);
}

TEST(DestinationTest, cast_remote)
{
    Remote remote(Address("Olsztyn", "10-555", "Baltycka", "4", "Klatka H6"));
    Destination &dst = remote;
    ASSERT_EQ(typeid(dst), typeid(remote));
    ASSERT_EQ(dynamic_cast<Remote &>(dst).address.postalCode, "10-555");
}

TEST(DishTest, initialization)
{
    std::string name = "Pierogi";
    std::string description = "Ręcznnie lepione pierogi z mięsem, smaożone na maśle";
    unsigned int price = 1999;
    std::string ingredients = "mięso, mąka, woda, cebula, przyprawy";
    unsigned int volume = 300;

    Dish pierogi(name, description, price, ingredients, volume);

    ASSERT_EQ(pierogi.name, name);
    ASSERT_EQ(pierogi.description, description);
    ASSERT_EQ(pierogi.price, price);
    ASSERT_EQ(pierogi.ingredients, ingredients);
    ASSERT_EQ(pierogi.unit, UNIT::g);
    ASSERT_EQ(pierogi.volume, volume);
}

TEST(BeverageTest, initialization)
{
    std::string name = "Woda";
    std::string description = "Woda mineralna niegazowana";
    unsigned int price = 299;
    unsigned int alcoholPercentage = 0;
    unsigned int volume = 500;

    Beverage woda(name, description, price, alcoholPercentage, volume);

    ASSERT_EQ(woda.name, name);
    ASSERT_EQ(woda.description, description);
    ASSERT_EQ(woda.price, price);
    ASSERT_EQ(woda.alcoholPercentage, alcoholPercentage);
    ASSERT_EQ(woda.unit, UNIT::ml);
    ASSERT_EQ(woda.volume, volume);
}

TEST(MenuItemTest, cast_dish)
{
    Dish pierogi("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", 1999, "mięso, mąka, woda, cebula, przyprawy", 300);
    MenuItem &item = pierogi;
    ASSERT_EQ(typeid(item), typeid(pierogi));
    ASSERT_EQ(dynamic_cast<Dish &>(item).ingredients, "mięso, mąka, woda, cebula, przyprawy");
}

TEST(MenuItemTest, cast_beverage)
{
    Beverage woda("Woda", "Woda mineralna niegazowana", 299, 0, 500);
    MenuItem &item = woda;
    ASSERT_EQ(typeid(item), typeid(woda));
    ASSERT_EQ(dynamic_cast<Beverage &>(item).alcoholPercentage, 0);
}

TEST(MenuTest, initialization)
{

    std::vector<Beverage> beverages;
    beverages.push_back(Beverage("Coca Cola", "Refreshing cola drink", 199, 0, 330));
    beverages.push_back(Beverage("Orange Juice", "Freshly squeezed orange juice", 299, 0, 250));

    std::vector<Dish> dishes;
    dishes.push_back(Dish("Pizza", "Pizza Neapoletana", 1499, "dough, tomato sauce, cheese, toppings", 500));
    dishes.push_back(Dish("Burger", "Burger with fries and vegetables", 1299, "beef patty, cheese, lettuce, tomato, onion", 300));

    Menu menu(beverages, dishes);
    ASSERT_EQ(menu.beverages.size(), 2);
    ASSERT_EQ(menu.dishes.size(), 2);
}

TEST(ServerHandlerTest, initialization_and_reading_config)
{
    ASSERT_NO_THROW(ServerHandler sh = ServerHandler());
}

TEST(ServerHandlerTest, fetchMenu)
{
    ServerHandler sh = ServerHandler();
    Menu menu = sh.fetchMenu();
    ASSERT_TRUE(menu.menuItems.size() != 0);
}
