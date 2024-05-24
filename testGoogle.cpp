#include <gtest/gtest.h>
#include <unistd.h>
#include "address.h"
#include "destination.h"
#include "menuItem.h"
#include "orderitem.h"
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

TEST(TableTest, get_typical)
{
    Table tbl(Table::Position(3, 5, 0), 4);
    ASSERT_EQ(&tbl, &(tbl.get()));
}

TEST(RemoteTest, create_typical)
{
    Address adr("Olsztyn", "10-555", "Baltycka", "4", "Klatka H6");
    Remote remote("Elzbieta Kopyto", "123456789", adr);
    ASSERT_EQ(remote.name, "Elzbieta Kopyto");
    ASSERT_EQ(remote.phoneNumber, "123456789");
    ASSERT_EQ(remote.address.city, "Olsztyn");
}

TEST(RemoteTest, get_typical)
{
    Address adr("Olsztyn", "10-555", "Baltycka", "4", "Klatka H6");
    Remote remote("Elzbieta Kopyto", "123456789", adr);
    ASSERT_EQ(&remote, &(remote.get()));
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
    Remote remote("Elzbieta Kopyto", "123456789", Address("Olsztyn", "10-555", "Baltycka", "4", "Klatka H6"));
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
    MenuItem::CATEGORY category = MenuItem::CATEGORY::mainCourse;

    Dish pierogi(name, description, category, price, ingredients, volume);

    ASSERT_EQ(pierogi.name, name);
    ASSERT_EQ(pierogi.description, description);
    ASSERT_EQ(pierogi.price, price);
    ASSERT_EQ(pierogi.category, category);
    ASSERT_EQ(pierogi.ingredients, ingredients);
    ASSERT_EQ(pierogi.unit, MenuItem::UNIT::g);
    ASSERT_EQ(pierogi.volume, volume);
}

TEST(BeverageTest, initialization)
{
    MenuItem::CATEGORY category = MenuItem::CATEGORY::coldBeverage;
    std::string name = "Woda";
    std::string description = "Woda mineralna niegazowana";
    unsigned int price = 299;
    unsigned int alcoholPercentage = 0;
    unsigned int volume = 500;

    Beverage woda(name, description, category, price, alcoholPercentage, volume);

    ASSERT_EQ(woda.name, name);
    ASSERT_EQ(woda.description, description);
    ASSERT_EQ(woda.category, category);
    ASSERT_EQ(woda.price, price);
    ASSERT_EQ(woda.alcoholPercentage, alcoholPercentage);
    ASSERT_EQ(woda.unit, MenuItem::UNIT::ml);
    ASSERT_EQ(woda.volume, volume);
}

TEST(MenuItemTest, cast_dish)
{
    MenuItem::CATEGORY category = MenuItem::CATEGORY::mainCourse;
    Dish pierogi("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", category, 1999, "mięso, mąka, woda, cebula, przyprawy", 300);
    MenuItem &item = pierogi;
    ASSERT_EQ(typeid(item), typeid(pierogi));
    ASSERT_EQ(dynamic_cast<Dish &>(item).ingredients, "mięso, mąka, woda, cebula, przyprawy");
}

TEST(MenuItemTest, cast_beverage)
{
    MenuItem::CATEGORY category = MenuItem::CATEGORY::coldBeverage;
    Beverage woda("Woda", "Woda mineralna niegazowana", category, 299, 0, 500);
    MenuItem &item = woda;
    ASSERT_EQ(typeid(item), typeid(woda));
    ASSERT_EQ(dynamic_cast<Beverage &>(item).alcoholPercentage, 0);
}

TEST(MenuTest, initialization)
{
    std::vector<std::unique_ptr<MenuItem>> items;

    MenuItem::CATEGORY category1 = MenuItem::CATEGORY::coldBeverage;
    items.push_back(std::make_unique<Beverage>("Coca Cola", "Refreshing cola drink", category1, 199, 0, 330));
    items.push_back(std::make_unique<Beverage>("Orange Juice", "Freshly squeezed orange juice", category1, 299, 0, 250));

    MenuItem::CATEGORY category2 = MenuItem::CATEGORY::pizza;
    MenuItem::CATEGORY category3 = MenuItem::CATEGORY::burger;
    items.push_back(std::make_unique<Dish>("Pizza", "Pizza Neapoletana", category2, 1499, "dough, tomato sauce, cheese, toppings", 500));
    items.push_back(std::make_unique<Dish>("Burger", "Burger with fries and vegetables", category3, 1299, "beef patty, cheese, lettuce, tomato, onion", 300));

    Menu menu(std::move(items));
    ASSERT_EQ(menu.menuItems.size(), 4);
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

TEST(OrderItemTest, create_typical)
{
    Dish pierogi("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", MenuItem::CATEGORY::mainCourse, 1999, "mięso, mąka, woda, cebula, przyprawy", 300);
    OrderItem orderit1(pierogi, 1);
    ASSERT_EQ(orderit1.menuItem.name, "Pierogi");
    ASSERT_EQ(orderit1.quantity, 1);
    ASSERT_EQ(orderit1.getDiscount(), 0);
    ASSERT_EQ(orderit1.getComment(), "");
    ASSERT_EQ(orderit1.getStatus(), OrderItem::ItemStatus::ordered);
}

TEST(OrderItemTest, create_with_comment)
{
    Dish pierogi("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", MenuItem::CATEGORY::mainCourse, 1999, "mięso, mąka, woda, cebula, przyprawy", 300);
    OrderItem orderit1(pierogi, 1, "Bez masla");
    ASSERT_EQ(orderit1.getComment(), "Bez masla");
    std::string com;
    for (int i = 1; i <= 255; i++)
        com += "a";
    OrderItem orderit2(pierogi, 1, com);
    ASSERT_EQ(orderit2.getComment(), com);
}

TEST(OrderItemTest, create_with_discount)
{
    Dish pierogi("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", MenuItem::CATEGORY::mainCourse, 1999, "mięso, mąka, woda, cebula, przyprawy", 300);
    OrderItem orderit1(pierogi, 1, "", 20);
    ASSERT_EQ(orderit1.getDiscount(), 20);
    OrderItem orderit2(pierogi, 1, "", 100);
    ASSERT_EQ(orderit2.getDiscount(), 100);
}

TEST(OrderItemTest, create_too_long_comment)
{
    Dish pierogi("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", MenuItem::CATEGORY::mainCourse, 1999, "mięso, mąka, woda, cebula, przyprawy", 300);
    std::string com;
    for (int i = 1; i <= 256; i++)
        com += "a";
    EXPECT_THROW(OrderItem(pierogi, 1, com), std::invalid_argument);
}

TEST(OrderItemTest, create_too_big_discount)
{
    Dish pierogi("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", MenuItem::CATEGORY::mainCourse, 1999, "mięso, mąka, woda, cebula, przyprawy", 300);
    EXPECT_THROW(OrderItem(pierogi, 1, "", 101), std::invalid_argument);
}

TEST(OrderItemTest, create_zero_quantity)
{
    Dish pierogi("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", MenuItem::CATEGORY::mainCourse, 1999, "mięso, mąka, woda, cebula, przyprawy", 300);
    EXPECT_THROW(OrderItem(pierogi, 0), std::invalid_argument);
}

TEST(OrderItemTest, addComment_typical)
{
    Dish pierogi("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", MenuItem::CATEGORY::mainCourse, 1999, "mięso, mąka, woda, cebula, przyprawy", 300);
    OrderItem orderit1(pierogi, 1);
    orderit1.addComment("Połowa porcji");
    ASSERT_EQ(orderit1.getComment(), "Połowa porcji");
    std::string com;
    for (int i = 1; i <= 255; i++)
        com += "a";
    orderit1.addComment(com);
    ASSERT_EQ(orderit1.getComment(), com);
    orderit1.addComment("");
    ASSERT_EQ(orderit1.getComment(), "");
}

TEST(OrderItemTest, addComment_too_long)
{
    Dish pierogi("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", MenuItem::CATEGORY::mainCourse, 1999, "mięso, mąka, woda, cebula, przyprawy", 300);
    OrderItem orderit1(pierogi, 1);
    std::string com;
    for (int i = 1; i <= 256; i++)
        com += "a";
    EXPECT_THROW(orderit1.addComment(com), std::invalid_argument);
}

TEST(OrderItemTest, add_discount_typical)
{
    Dish pierogi("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", MenuItem::CATEGORY::mainCourse, 1999, "mięso, mąka, woda, cebula, przyprawy", 300);
    OrderItem orderit1(pierogi, 1);
    orderit1.setDiscount(40);
    ASSERT_EQ(orderit1.getDiscount(), 40);
    orderit1.setDiscount(100);
    ASSERT_EQ(orderit1.getDiscount(), 100);
    orderit1.setDiscount(0);
    ASSERT_EQ(orderit1.getDiscount(), 0);
}

TEST(OrderItemTest, add_discount_too_big)
{
    Dish pierogi("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", MenuItem::CATEGORY::mainCourse, 1999, "mięso, mąka, woda, cebula, przyprawy", 300);
    OrderItem orderit1(pierogi, 1);
    EXPECT_THROW(orderit1.setDiscount(101), std::invalid_argument);
}

TEST(OrderItemTest, setDelivered_typical)
{
    // TODO
}

TEST(OrderItemTest, setDelivered_while_not_ready)
{
    Dish pierogi("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", MenuItem::CATEGORY::mainCourse, 1999, "mięso, mąka, woda, cebula, przyprawy", 300);
    OrderItem orderit1(pierogi, 1);
    ASSERT_EQ(orderit1.getStatus(), OrderItem::ItemStatus::ordered);
    EXPECT_THROW(orderit1.setDelivered(), std::runtime_error);
}

TEST(OrderItemTest, setCancelled_typical)
{
    Dish pierogi("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", MenuItem::CATEGORY::mainCourse, 1999, "mięso, mąka, woda, cebula, przyprawy", 300);
    OrderItem orderit1(pierogi, 1);
    ASSERT_EQ(orderit1.getStatus(), OrderItem::ItemStatus::ordered);
    orderit1.setCancelled();
    ASSERT_EQ(orderit1.getStatus(), OrderItem::ItemStatus::canceled);
}

TEST(OrderItemTest, getPrice_typical)
{
    Dish pierogi("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", MenuItem::CATEGORY::mainCourse, 1999, "mięso, mąka, woda, cebula, przyprawy", 300);
    OrderItem orderit1(pierogi, 1);
    ASSERT_EQ(orderit1.getPrice(), 1999);
    OrderItem orderit2(pierogi, 3);
    ASSERT_EQ(orderit2.getPrice(), 3 * 1999);
}

TEST(OrderItemTest, getWaitingTime_typical)
{
    Dish pierogi("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", MenuItem::CATEGORY::mainCourse, 1999, "mięso, mąka, woda, cebula, przyprawy", 300);
    OrderItem orderit1(pierogi, 1);
    sleep(3);
    ASSERT_EQ(orderit1.getWaitingTime(), 3);
    sleep(2);
    ASSERT_EQ(orderit1.getWaitingTime(), 5);
}
