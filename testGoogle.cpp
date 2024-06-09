#include <gtest/gtest.h>
#include <unistd.h>
#include "restaurant.h"

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
}

TEST(TableTest, occupy)
{
    Table tbl(Table::Position(3, 5, 0), 4);
    ASSERT_EQ(tbl.isOccupied(), false);

    LocalOrder lo(tbl);
    ASSERT_EQ(tbl.isOccupied(), true);

    lo.setClosed();
    ASSERT_EQ(tbl.isOccupied(), false);
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
    MenuItem::Category category = MenuItem::Category::mainCourse;

    Dish pierogi(name, description, category, price, ingredients, volume);

    ASSERT_EQ(pierogi.name, name);
    ASSERT_EQ(pierogi.description, description);
    ASSERT_EQ(pierogi.price, price);
    ASSERT_EQ(pierogi.category, category);
    ASSERT_EQ(pierogi.ingredients, ingredients);
    ASSERT_EQ(pierogi.unit, MenuItem::Unit::g);
    ASSERT_EQ(pierogi.volume, volume);
}

TEST(BeverageTest, initialization)
{
    MenuItem::Category category = MenuItem::Category::coldBeverage;
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
    ASSERT_EQ(woda.unit, MenuItem::Unit::ml);
    ASSERT_EQ(woda.volume, volume);
}

TEST(BeverageTest, getVolume_typical)
{
    MenuItem::Category category = MenuItem::Category::coldBeverage;
    std::string name = "Woda";
    std::string description = "Woda mineralna niegazowana";
    unsigned int price = 299;
    unsigned int alcoholPercentage = 0;
    unsigned int volume = 500;

    Beverage woda(name, description, category, price, alcoholPercentage, volume);

    ASSERT_EQ(woda.getVolumeStr(), "500ml");
}

TEST(MenuItemTest, cast_dish)
{
    MenuItem::Category category = MenuItem::Category::mainCourse;
    Dish pierogi("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", category, 1999, "mięso, mąka, woda, cebula, przyprawy", 300);
    MenuItem &item = pierogi;
    ASSERT_EQ(typeid(item), typeid(pierogi));
    ASSERT_EQ(dynamic_cast<Dish &>(item).ingredients, "mięso, mąka, woda, cebula, przyprawy");
}

TEST(MenuItemTest, cast_beverage)
{
    MenuItem::Category category = MenuItem::Category::coldBeverage;
    Beverage woda("Woda", "Woda mineralna niegazowana", category, 299, 0, 500);
    MenuItem &item = woda;
    ASSERT_EQ(typeid(item), typeid(woda));
    ASSERT_EQ(dynamic_cast<Beverage &>(item).alcoholPercentage, 0);
}


TEST(MenuItemTest, getPriceStr_typical)
{
    std::string name = "Pierogi";
    std::string description = "Ręcznnie lepione pierogi z mięsem, smaożone na maśle";
    unsigned int price = 1999;
    std::string ingredients = "mięso, mąka, woda, cebula, przyprawy";
    unsigned int volume = 300;
    MenuItem::Category category = MenuItem::Category::mainCourse;

    Dish pierogi(name, description, category, price, ingredients, volume);
    MenuItem& mi = pierogi;

    ASSERT_EQ(mi.getPriceStr(), "19,99");
}

TEST(MenuItemTest, getPriceStr_less_than_10_fractions)
{
    std::string name = "Pierogi";
    std::string description = "Ręcznnie lepione pierogi z mięsem, smaożone na maśle";
    unsigned int price = 1905;
    std::string ingredients = "mięso, mąka, woda, cebula, przyprawy";
    unsigned int volume = 300;
    MenuItem::Category category = MenuItem::Category::mainCourse;

    Dish pierogi(name, description, category, price, ingredients, volume);
    MenuItem& mi = pierogi;

    ASSERT_EQ(mi.getPriceStr(), "19,05");
}

TEST(MenuItemTest, getPriceStr_zero)
{
    std::string name = "Pierogi";
    std::string description = "Ręcznnie lepione pierogi z mięsem, smaożone na maśle";
    unsigned int price = 0;
    std::string ingredients = "mięso, mąka, woda, cebula, przyprawy";
    unsigned int volume = 300;
    MenuItem::Category category = MenuItem::Category::mainCourse;

    Dish pierogi(name, description, category, price, ingredients, volume);
    MenuItem& mi = pierogi;

    ASSERT_EQ(mi.getPriceStr(), "0,00");
}

TEST(MenuItemTest, getVolumeStr_grams)
{
    std::string name = "Pierogi";
    std::string description = "Ręcznnie lepione pierogi z mięsem, smaożone na maśle";
    unsigned int price = 0;
    std::string ingredients = "mięso, mąka, woda, cebula, przyprawy";
    unsigned int volume = 300;
    MenuItem::Category category = MenuItem::Category::mainCourse;

    Dish pierogi(name, description, category, price, ingredients, volume);
    MenuItem& mi = pierogi;

    ASSERT_EQ(mi.getVolumeStr(), "300g");
}

TEST(MenuItemTest, getVolumeStr_ml)
{
    MenuItem::Category category = MenuItem::Category::coldBeverage;
    Beverage woda("Woda", "Woda mineralna niegazowana", category, 299, 0, 500);
    MenuItem &mi = woda;

    ASSERT_EQ(mi.getVolumeStr(), "500ml");
}

TEST(MenuItemTest, getVolumeStr_piece)
{
    Dish ciacho("Ciacho", "Slodkie ciacho", MenuItem::Category::desert, 1999,
        "maka", 1, MenuItem::Unit::piece);
    MenuItem &mi = ciacho;

    ASSERT_EQ(mi.getVolumeStr(), "1pc");
}

TEST(MenuTest, initialization)
{
    std::vector<std::unique_ptr<MenuItem>> items;

    MenuItem::Category category1 = MenuItem::Category::coldBeverage;
    items.push_back(std::make_unique<Beverage>("Coca Cola", "Refreshing cola drink", category1, 199, 0, 330));
    items.push_back(std::make_unique<Beverage>("Orange Juice", "Freshly squeezed orange juice", category1, 299, 0, 250));

    MenuItem::Category category2 = MenuItem::Category::pizza;
    MenuItem::Category category3 = MenuItem::Category::burger;
    items.push_back(std::make_unique<Dish>("Pizza", "Pizza Neapoletana", category2, 1499, "dough, tomato sauce, cheese, toppings", 500));
    items.push_back(std::make_unique<Dish>("Burger", "Burger with fries and vegetables", category3, 1299, "beef patty, cheese, lettuce, tomato, onion", 300));

    Menu menu(std::move(items));
    ASSERT_EQ(menu.size(), 4);
}

TEST(MenuTest, iteration_typical)
{
    std::vector<std::unique_ptr<MenuItem>> items;

    MenuItem::Category category1 = MenuItem::Category::coldBeverage;
    items.push_back(std::make_unique<Beverage>("Coca Cola", "Refreshing cola drink", category1, 199, 0, 330));
    items.push_back(std::make_unique<Beverage>("Orange Juice", "Freshly squeezed orange juice", category1, 299, 0, 250));

    MenuItem::Category category2 = MenuItem::Category::pizza;
    MenuItem::Category category3 = MenuItem::Category::burger;
    items.push_back(std::make_unique<Dish>("Pizza", "Pizza Neapoletana", category2, 1499, "dough, tomato sauce, cheese, toppings", 500));
    items.push_back(std::make_unique<Dish>("Burger", "Burger with fries and vegetables", category3, 1299, "beef patty, cheese, lettuce, tomato, onion", 300));

    Menu menu(std::move(items));

    auto menu_it = menu.mibegin();
    ASSERT_EQ((*menu_it).name, "Coca Cola");
    ASSERT_EQ((*++menu_it).name, "Orange Juice");
    ASSERT_EQ((*++menu_it).name, "Pizza");
    ASSERT_EQ((*++menu_it).name, "Burger");
    ASSERT_EQ(++menu_it != menu.miend(), false);
}

TEST(OrderItemTest, create_typical)
{
    Dish pierogi("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", MenuItem::Category::mainCourse, 1999, "mięso, mąka, woda, cebula, przyprawy", 300);
    OrderItem orderit1(pierogi, 1);
    ASSERT_EQ(orderit1.menuItem.name, "Pierogi");
    ASSERT_EQ(orderit1.quantity, 1);
    ASSERT_EQ(orderit1.getDiscount(), 0);
    ASSERT_EQ(orderit1.getComment(), "");
    ASSERT_EQ(orderit1.getStatus(), ItemStatus::created);
}

TEST(OrderItemTest, create_with_comment)
{
    Dish pierogi("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", MenuItem::Category::mainCourse, 1999, "mięso, mąka, woda, cebula, przyprawy", 300);
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
    Dish pierogi("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", MenuItem::Category::mainCourse, 1999, "mięso, mąka, woda, cebula, przyprawy", 300);
    OrderItem orderit1(pierogi, 1, "", 20);
    ASSERT_EQ(orderit1.getDiscount(), 20);
    OrderItem orderit2(pierogi, 1, "", 100);
    ASSERT_EQ(orderit2.getDiscount(), 100);
}

TEST(OrderItemTest, create_too_long_comment)
{
    Dish pierogi("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", MenuItem::Category::mainCourse, 1999, "mięso, mąka, woda, cebula, przyprawy", 300);
    std::string com;
    for (int i = 1; i <= 256; i++)
        com += "a";
    EXPECT_THROW(OrderItem(pierogi, 1, com), std::invalid_argument);
}

TEST(OrderItemTest, create_too_big_discount)
{
    Dish pierogi("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", MenuItem::Category::mainCourse, 1999, "mięso, mąka, woda, cebula, przyprawy", 300);
    EXPECT_THROW(OrderItem(pierogi, 1, "", 101), std::invalid_argument);
}

TEST(OrderItemTest, create_zero_quantity)
{
    Dish pierogi("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", MenuItem::Category::mainCourse, 1999, "mięso, mąka, woda, cebula, przyprawy", 300);
    EXPECT_THROW(OrderItem(pierogi, 0), std::invalid_argument);
}

TEST(OrderItemTest, addComment_typical)
{
    Dish pierogi("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", MenuItem::Category::mainCourse, 1999, "mięso, mąka, woda, cebula, przyprawy", 300);
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
    Dish pierogi("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", MenuItem::Category::mainCourse, 1999, "mięso, mąka, woda, cebula, przyprawy", 300);
    OrderItem orderit1(pierogi, 1);
    std::string com;
    for (int i = 1; i <= 256; i++)
        com += "a";
    EXPECT_THROW(orderit1.addComment(com), std::invalid_argument);
}

TEST(OrderItemTest, addComment_move_typical)
{
    Dish pierogi("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", MenuItem::Category::mainCourse, 1999, "mięso, mąka, woda, cebula, przyprawy", 300);
    OrderItem orderit1(pierogi, 1);
    orderit1.addComment(std::move("Połowa porcji"));
    ASSERT_EQ(orderit1.getComment(), "Połowa porcji");
    orderit1.addComment(std::move(""));
    ASSERT_EQ(orderit1.getComment(), "");
}

TEST(OrderItemTest, add_discount_typical)
{
    Dish pierogi("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", MenuItem::Category::mainCourse, 1999, "mięso, mąka, woda, cebula, przyprawy", 300);
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
    Dish pierogi("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", MenuItem::Category::mainCourse, 1999, "mięso, mąka, woda, cebula, przyprawy", 300);
    OrderItem orderit(pierogi, 1);
    EXPECT_THROW(orderit.setDiscount(101), std::invalid_argument);
}

TEST(OrderItemTest, changeStatus_typical)
{
    Dish pierogi("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", MenuItem::Category::mainCourse, 1999, "mięso, mąka, woda, cebula, przyprawy", 300);
    OrderItem orderit(pierogi, 1);

    ASSERT_EQ(orderit.getStatus(), ItemStatus::created);

    orderit.changeStatus(ItemStatus::ordered);
    ASSERT_EQ(orderit.getStatus(), ItemStatus::ordered);

    orderit.changeStatus(ItemStatus::inPreparation);
    ASSERT_EQ(orderit.getStatus(), ItemStatus::inPreparation);

    orderit.changeStatus(ItemStatus::readyToDeliver);
    ASSERT_EQ(orderit.getStatus(), ItemStatus::readyToDeliver);

    orderit.changeStatus(ItemStatus::delivered);
    ASSERT_EQ(orderit.getStatus(), ItemStatus::delivered);
}

TEST(OrderItemTest, changeStatus_delivered_canceled)
{
    Dish pierogi("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", MenuItem::Category::mainCourse, 1999, "mięso, mąka, woda, cebula, przyprawy", 300);
    OrderItem orderit(pierogi, 1);

    orderit.changeStatus(ItemStatus::delivered);
    ASSERT_EQ(orderit.getStatus(), ItemStatus::delivered);
    EXPECT_THROW(orderit.changeStatus(ItemStatus::canceled), std::runtime_error);

    OrderItem orderit2(pierogi, 1);
    orderit2.changeStatus(ItemStatus::canceled);
    EXPECT_THROW(orderit.changeStatus(ItemStatus::delivered), std::runtime_error);
}

TEST(OrderItemTest, changeStatus_decrease)
{
    Dish pierogi("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", MenuItem::Category::mainCourse, 1999, "mięso, mąka, woda, cebula, przyprawy", 300);
    OrderItem orderit(pierogi, 1);

    orderit.changeStatus(ItemStatus::ordered);
    ASSERT_EQ(orderit.getStatus(), ItemStatus::ordered);
    EXPECT_THROW(orderit.changeStatus(ItemStatus::created), std::runtime_error);

    orderit.changeStatus(ItemStatus::inPreparation);
    ASSERT_EQ(orderit.getStatus(), ItemStatus::inPreparation);
    EXPECT_THROW(orderit.changeStatus(ItemStatus::created), std::runtime_error);
    EXPECT_THROW(orderit.changeStatus(ItemStatus::ordered), std::runtime_error);

    orderit.changeStatus(ItemStatus::readyToDeliver);
    ASSERT_EQ(orderit.getStatus(), ItemStatus::readyToDeliver);
    EXPECT_THROW(orderit.changeStatus(ItemStatus::created), std::runtime_error);
    EXPECT_THROW(orderit.changeStatus(ItemStatus::ordered), std::runtime_error);
    EXPECT_THROW(orderit.changeStatus(ItemStatus::inPreparation), std::runtime_error);

    orderit.changeStatus(ItemStatus::delivered);
    ASSERT_EQ(orderit.getStatus(), ItemStatus::delivered);
    EXPECT_THROW(orderit.changeStatus(ItemStatus::created), std::runtime_error);
    EXPECT_THROW(orderit.changeStatus(ItemStatus::ordered), std::runtime_error);
    EXPECT_THROW(orderit.changeStatus(ItemStatus::inPreparation), std::runtime_error);
    EXPECT_THROW(orderit.changeStatus(ItemStatus::readyToDeliver), std::runtime_error);
    EXPECT_THROW(orderit.changeStatus(ItemStatus::canceled), std::runtime_error);
}

TEST(OrderItemTest, changeStatus_cancel)
{
    Dish pierogi("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", MenuItem::Category::mainCourse, 1999, "mięso, mąka, woda, cebula, przyprawy", 300);
    OrderItem orderit(pierogi, 1);

    ASSERT_EQ(orderit.getStatus(), ItemStatus::created);
    orderit.changeStatus(ItemStatus::canceled);
    ASSERT_EQ(orderit.getStatus(), ItemStatus::canceled);

    EXPECT_THROW(orderit.changeStatus(ItemStatus::created), std::runtime_error);
    EXPECT_THROW(orderit.changeStatus(ItemStatus::ordered), std::runtime_error);
    EXPECT_THROW(orderit.changeStatus(ItemStatus::inPreparation), std::runtime_error);
    EXPECT_THROW(orderit.changeStatus(ItemStatus::readyToDeliver), std::runtime_error);
    EXPECT_THROW(orderit.changeStatus(ItemStatus::delivered), std::runtime_error);

    OrderItem orderit2(pierogi, 1);
    orderit2.changeStatus(ItemStatus::ordered);
    orderit2.changeStatus(ItemStatus::canceled);
    ASSERT_EQ(orderit2.getStatus(), ItemStatus::canceled);

    OrderItem orderit3(pierogi, 1);
    orderit3.changeStatus(ItemStatus::inPreparation);
    orderit3.changeStatus(ItemStatus::canceled);
    ASSERT_EQ(orderit3.getStatus(), ItemStatus::canceled);

    OrderItem orderit4(pierogi, 1);
    orderit4.changeStatus(ItemStatus::readyToDeliver);
    orderit4.changeStatus(ItemStatus::canceled);
    ASSERT_EQ(orderit4.getStatus(), ItemStatus::canceled);

    OrderItem orderit5(pierogi, 1);
    orderit5.changeStatus(ItemStatus::delivered);
    EXPECT_THROW(orderit5.changeStatus(ItemStatus::canceled), std::runtime_error);
}

TEST(OrderItemTest, setDelivered_typical)
{
    Dish pierogi("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", MenuItem::Category::mainCourse, 1999, "mięso, mąka, woda, cebula, przyprawy", 300);
    OrderItem orderit(pierogi, 1);
    orderit.changeStatus(ItemStatus::readyToDeliver);
    orderit.setDelivered();
    ASSERT_EQ(orderit.getStatus(), ItemStatus::delivered);
}

TEST(OrderItemTest, setDelivered_while_not_ready)
{
    Dish pierogi("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", MenuItem::Category::mainCourse, 1999, "mięso, mąka, woda, cebula, przyprawy", 300);
    OrderItem orderit(pierogi, 1);
    ASSERT_EQ(orderit.getStatus(), ItemStatus::created);
    EXPECT_THROW(orderit.setDelivered(), std::runtime_error);
    orderit.changeStatus(ItemStatus::ordered);
    EXPECT_THROW(orderit.setDelivered(), std::runtime_error);
    orderit.changeStatus(ItemStatus::inPreparation);
    EXPECT_THROW(orderit.setDelivered(), std::runtime_error);
}

TEST(OrderItemTest, setCancelled_typical)
{
    Dish pierogi("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", MenuItem::Category::mainCourse, 1999, "mięso, mąka, woda, cebula, przyprawy", 300);
    OrderItem orderit1(pierogi, 1);

    ASSERT_EQ(orderit1.getStatus(), ItemStatus::created);
    orderit1.setCancelled();
    ASSERT_EQ(orderit1.getStatus(), ItemStatus::canceled);

    OrderItem orderit2(pierogi, 1);
    orderit2.changeStatus(ItemStatus::ordered);
    orderit2.setCancelled();
    ASSERT_EQ(orderit2.getStatus(), ItemStatus::canceled);
}

TEST(OrderItemTest, setCancelled_after_ordered)
{
    Dish pierogi("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", MenuItem::Category::mainCourse, 1999, "mięso, mąka, woda, cebula, przyprawy", 300);
    OrderItem orderit(pierogi, 1);

    orderit.changeStatus(ItemStatus::inPreparation);
    EXPECT_THROW(orderit.setCancelled(), std::runtime_error);

    orderit.changeStatus(ItemStatus::readyToDeliver);
    EXPECT_THROW(orderit.setCancelled(), std::runtime_error);

    orderit.changeStatus(ItemStatus::delivered);
    EXPECT_THROW(orderit.setCancelled(), std::runtime_error);
}

TEST(OrderItemTest, getPrice_typical)
{
    Dish pierogi("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", MenuItem::Category::mainCourse, 1999, "mięso, mąka, woda, cebula, przyprawy", 300);
    OrderItem orderit1(pierogi, 1);
    ASSERT_EQ(orderit1.getPrice(), 1999);
    OrderItem orderit2(pierogi, 3);
    ASSERT_EQ(orderit2.getPrice(), 3 * 1999);
}

TEST(OrderItemTest, getPrice_discount_typical)
{
    Dish pierogi("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", MenuItem::Category::mainCourse, 1999, "mięso, mąka, woda, cebula, przyprawy", 300);
    OrderItem orderit1(pierogi, 3);
    ASSERT_EQ(orderit1.getPrice(), 3 * 1999);
    orderit1.setDiscount(5);
    ASSERT_EQ(orderit1.getPrice(), 5697);
    orderit1.setDiscount(1);
    ASSERT_EQ(orderit1.getPrice(), 5937);
    orderit1.setDiscount(99);
    ASSERT_EQ(orderit1.getPrice(), 59);
    orderit1.setDiscount(100);
    ASSERT_EQ(orderit1.getPrice(), 0);
}

TEST(OrderItemTest, getPrice_discount_big_price)
{
    Dish pierogi("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", MenuItem::Category::mainCourse, 2345678, "mięso, mąka, woda, cebula, przyprawy", 300);
    OrderItem orderit1(pierogi, 7);
    ASSERT_EQ(orderit1.getPrice(), 7 * 2345678);
    orderit1.setDiscount(1);
    ASSERT_EQ(orderit1.getPrice(), 16255548);
    orderit1.setDiscount(13);
    ASSERT_EQ(orderit1.getPrice(), 14285179);
    orderit1.setDiscount(97);
    ASSERT_EQ(orderit1.getPrice(), 492592);
    orderit1.setDiscount(100);
    ASSERT_EQ(orderit1.getPrice(), 0);

    Dish pierogi2("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", MenuItem::Category::mainCourse, 42949600, "mięso, mąka, woda, cebula, przyprawy", 300);
    OrderItem orderit2(pierogi2, 1);
    ASSERT_EQ(orderit2.getPrice(), 42949600);
    orderit2.setDiscount(1);
    ASSERT_EQ(orderit2.getPrice(), 42520104);
    orderit2.setDiscount(17);
    ASSERT_EQ(orderit2.getPrice(), 35648168);
    orderit2.setDiscount(99);
    ASSERT_EQ(orderit2.getPrice(), 429496);
    orderit2.setDiscount(100);
    ASSERT_EQ(orderit2.getPrice(), 0);
}

TEST(OrderItemTest, getPrice_discount_too_big_price)
{
    Dish pierogi("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", MenuItem::Category::mainCourse, 42949601, "mięso, mąka, woda, cebula, przyprawy", 300);
    OrderItem orderit1(pierogi, 1);
    EXPECT_THROW(orderit1.getPrice(), std::runtime_error);
}

TEST(OrderItemTest, getWaitingTime_typical)
{
    Dish pierogi("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", MenuItem::Category::mainCourse, 1999, "mięso, mąka, woda, cebula, przyprawy", 300);
    OrderItem orderit1(pierogi, 1);
    sleep(3);
    ASSERT_EQ(orderit1.getWaitingTime(), 3);
    sleep(2);
    ASSERT_EQ(orderit1.getWaitingTime(), 5);
}

TEST(OrderTest, create_LocalOrder)
{
    Table tbl(Table::Position(3, 5, 0), 4);
    LocalOrder lo(tbl);

    ASSERT_EQ(lo.table.position.x, 3);
    ASSERT_EQ(lo.table.position.y, 5);
    ASSERT_EQ(lo.table.position.level, 0);
    ASSERT_EQ(lo.table.seats, 4);
    ASSERT_EQ(tbl.isOccupied(), true);
}

TEST(OrderTest, create_LocalOrder_occupied_table)
{
    Table tbl(Table::Position(3, 5, 0), 4);
    LocalOrder lo(tbl);
    ASSERT_EQ(tbl.isOccupied(), true);
    EXPECT_THROW(LocalOrder lo2(tbl), std::runtime_error);
}

TEST(OrderTest, create_LocalOrder_free_table)
{
    Table tbl(Table::Position(3, 5, 0), 4);
    LocalOrder lo(tbl);
    ASSERT_EQ(tbl.isOccupied(), true);
    lo.setClosed();
    ASSERT_EQ(tbl.isOccupied(), false);
}

TEST(OrderTest, create_RemoteOrder)
{
    Remote rmt("Andrzej Kowal", "111111111", Address("Olsztyn", "00-000", "Kaliny", "5"));
    RemoteOrder ro(rmt);

    ASSERT_EQ(ro.remote.name, "Andrzej Kowal");
    ASSERT_EQ(ro.remote.phoneNumber, "111111111");
    ASSERT_EQ(ro.remote.address.city, "Olsztyn");
    ASSERT_EQ(ro.remote.address.postalCode, "00-000");
    ASSERT_EQ(ro.remote.address.street, "Kaliny");
    ASSERT_EQ(ro.remote.address.number, "5");
}

TEST(OrderTest, getDestinatin_LocalOrder)
{
    Table tbl(Table::Position(3, 5, 0), 4);
    LocalOrder lo(tbl);

    Order& o = dynamic_cast<Order&>(lo);

    const Table& tbl_ref = dynamic_cast<const Table&>(o.getDestination());

    ASSERT_EQ(tbl_ref.seats, 4);
}

TEST(OrderTest, getDestination_RemoteOrder)
{
    Remote rmt("Andrzej Kowal", "111111111", Address("Olsztyn", "00-000", "Kaliny", "5"));
    RemoteOrder ro(rmt);

    Order& o = dynamic_cast<Order&>(ro);

    const Remote& rmt_ref = dynamic_cast<const Remote&>(o.getDestination());

    ASSERT_EQ(rmt_ref.name, "Andrzej Kowal");
}

TEST(OrderTest, addOrderItem)
{
    Table tbl(Table::Position(3, 5, 0), 4);
    LocalOrder lo(tbl);

    const Dish pierogi("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", MenuItem::Category::mainCourse, 1999, "mięso, mąka, woda, cebula, przyprawy", 300);

    lo.addOrderItem(pierogi, 5);
    ASSERT_EQ(lo[0].getPrice(), 9995);
}

TEST(OrderTest, iterator_typical)
{
    Table tbl(Table::Position(3, 5, 0), 4);
    LocalOrder lo(tbl);

    const Dish pierogi("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", MenuItem::Category::mainCourse, 1999, "mięso, mąka, woda, cebula, przyprawy", 300);
    Beverage woda("Woda", "Woda mineralna niegazowana", Beverage::Category::coldBeverage, 299, 0, 500);

    lo.addOrderItem(pierogi, 5);
    lo.addOrderItem(woda, 2);

    auto it = lo.oibegin();
    ASSERT_EQ((*it).menuItem.name, "Pierogi");
    ASSERT_EQ((*++it).menuItem.name, "Woda");
    ASSERT_EQ(++it != lo.oiend(), false);
}

TEST(OrderTest, getOrderItem_typical)
{
    Table tbl(Table::Position(3, 5, 0), 4);
    LocalOrder lo(tbl);
    Order& ord = lo;

    const Dish pierogi("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", MenuItem::Category::mainCourse, 1999, "mięso, mąka, woda, cebula, przyprawy", 300);
    ord.addOrderItem(pierogi, 3);

    OrderItem& ordit = ord[0];
    ASSERT_EQ(ordit.quantity, 3);
    ASSERT_EQ(ordit.menuItem.name, "Pierogi");
}

TEST(OrderTest, getOrderItem_out_of_range)
{
    Table tbl(Table::Position(3, 5, 0), 4);
    LocalOrder lo(tbl);
    Order& ord = lo;

    const Dish pierogi("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", MenuItem::Category::mainCourse, 1999, "mięso, mąka, woda, cebula, przyprawy", 300);
    ord.addOrderItem(pierogi, 3);

    EXPECT_THROW(ord[2], std::invalid_argument);
}

TEST(OrderTest, getStatus_typical)
{
    Table tbl(Table::Position(3, 5, 0), 4);
    LocalOrder lo(tbl);
    Order& ord = lo;

    ASSERT_EQ(ord.getStatus(), OrderStatus::inProgress);
}

TEST(OrderTest, setClosed_typical)
{
    Table tbl(Table::Position(3, 5, 0), 4);
    LocalOrder lo(tbl);
    Order& ord = dynamic_cast<Order&>(lo);

    const Dish pierogi("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", MenuItem::Category::mainCourse, 1999, "mięso, mąka, woda, cebula, przyprawy", 300);
    const Beverage woda("Woda", "Woda mineralna niegazowana", Beverage::Category::coldBeverage, 299, 0, 500);

    ord.addOrderItem(pierogi, 3);
    ord.addOrderItem(woda, 2);

    ord[0].changeStatus(ItemStatus::delivered);
    ord[1].changeStatus(ItemStatus::canceled);

    ord.setClosed();
    ASSERT_EQ(ord.getStatus(), OrderStatus::closed);
}

TEST(OrderTest, setClosed_empty)
{
    Table tbl(Table::Position(3, 5, 0), 4);
    LocalOrder lo(tbl);
    Order& ord = dynamic_cast<Order&>(lo);

    ASSERT_EQ(ord.getStatus(), OrderStatus::inProgress);
    ord.setClosed();
    ASSERT_EQ(ord.getStatus(), OrderStatus::closed);
}

TEST(OrderTest, setClosed_double)
{
    Table tbl(Table::Position(3, 5, 0), 4);
    LocalOrder lo(tbl);
    Order& ord = dynamic_cast<Order&>(lo);

    ord.setClosed();
    ASSERT_EQ(ord.getStatus(), OrderStatus::closed);
    EXPECT_THROW(ord.setClosed(), std::runtime_error);
}

TEST(OrderTest, setClosed_changing_data)
{
    Table tbl(Table::Position(3, 5, 0), 4);
    LocalOrder lo(tbl);
    Order& ord = dynamic_cast<Order&>(lo);

    const Beverage woda("Woda", "Woda mineralna niegazowana", Beverage::Category::coldBeverage, 299, 0, 500);

    ord.setClosed();
    EXPECT_THROW(ord.addOrderItem(woda, 5), std::runtime_error);
    EXPECT_THROW(ord.getWaitingTime(), std::runtime_error);
    EXPECT_THROW(ord.resetWaitingTime(), std::runtime_error);
}

TEST(OrderTest, getOrderTime)
{
    Table tbl(Table::Position(3, 5, 0), 4);
    LocalOrder lo(tbl);
    Order& ord = lo;

    ASSERT_EQ(ord.getOrderTime(), time(NULL));
}

TEST(OrderTest, getOrderTimeStr_typical)
{
    Table tbl(Table::Position(3, 5, 0), 4);
    LocalOrder lo(tbl);
    Order& ord = lo;

    char buf[6];
    time_t now = time(NULL);
    strftime(buf, 6, "%H:%M", localtime(&now));
    std::string time_str(buf);

    ASSERT_EQ(ord.getOrderTimeStr(), time_str);
}

TEST(OrderTest, getWaitingTime_typical)
{
    Table tbl(Table::Position(3, 5, 0), 4);
    LocalOrder lo(tbl);
    Order& ord = lo;

    sleep(3);
    ASSERT_EQ(ord.getWaitingTime(), 3);
    sleep(1);
    ASSERT_EQ(ord.getWaitingTime(), 4);
}

TEST(OrderTest, getWaitingTimeStr_typical)
{
    Table tbl(Table::Position(3, 5, 0), 4);
    LocalOrder lo(tbl);
    Order& ord = lo;

    sleep(1);
    ASSERT_EQ(ord.getWaitingTimeStr(), "now");
}

TEST(OrderTest, resetWaitingTime_typical)
{
    Table tbl(Table::Position(3, 5, 0), 4);
    LocalOrder lo(tbl);
    Order& ord = lo;

    sleep(2);
    ASSERT_EQ(ord.getWaitingTime(), 2);
    ord.resetWaitingTime();
    sleep(1);
    ASSERT_EQ(ord.getWaitingTime(), 1);
}

TEST(OrderTest, getTotalPrice)
{
    Table tbl(Table::Position(3, 5, 0), 4);
    LocalOrder lo(tbl);
    Order& ord = lo;

    const Dish pierogi("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", MenuItem::Category::mainCourse, 1999, "mięso, mąka, woda, cebula, przyprawy", 300);
    const Beverage cola("Cola", "Niezdrowy napoj", MenuItem::Category::coldBeverage, 800, 0, 500);

    ord.addOrderItem(pierogi, 5);
    ord.addOrderItem(cola, 4);

    ASSERT_EQ(lo.getTotalPrice(), 13195);
}

TEST(OrderTest, getTotalPriceStr_typical)
{
    Table tbl(Table::Position(3, 5, 0), 4);
    LocalOrder lo(tbl);
    Order& ord = lo;

    const Dish pierogi("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", MenuItem::Category::mainCourse, 1999, "mięso, mąka, woda, cebula, przyprawy", 300);
    const Beverage cola("Cola", "Niezdrowy napoj", MenuItem::Category::coldBeverage, 800, 0, 500);

    ord.addOrderItem(pierogi, 5);
    ord.addOrderItem(cola, 4);

    ASSERT_EQ(lo.getTotalPriceStr(), "131,95");
}

TEST(OrderTest, getTotalPriceStr_zero)
{
    Table tbl(Table::Position(3, 5, 0), 4);
    LocalOrder lo(tbl);
    Order& ord = lo;

    ASSERT_EQ(ord.getTotalPriceStr(), "0,00");
}

TEST(OrderTest, getTotalPriceStr_less_than_10_fraction)
{
    Table tbl(Table::Position(3, 5, 0), 4);
    LocalOrder lo(tbl);
    Order& ord = lo;

    const Dish pierogi("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", MenuItem::Category::mainCourse, 1905, "mięso, mąka, woda, cebula, przyprawy", 300);
    ord.addOrderItem(pierogi, 1);

    ASSERT_EQ(lo.getTotalPriceStr(), "19,05");
}

TEST(OrderTest, getTotalPrice_caneled_items)
{
    Table tbl(Table::Position(3, 5, 0), 4);
    LocalOrder lo(tbl);
    Order& ord = lo;

    const Dish pierogi("Pierogi", "Ręcznnie lepione pierogi z mięsem, smaożone na maśle", MenuItem::Category::mainCourse, 1999, "mięso, mąka, woda, cebula, przyprawy", 300);
    const Beverage cola("Cola", "Niezdrowy napoj", MenuItem::Category::coldBeverage, 800, 0, 500);

    ord.addOrderItem(pierogi, 5);
    ord.addOrderItem(cola, 4);
    ord.addOrderItem(cola, 3);

    ord[1].changeStatus(ItemStatus::canceled);

    ASSERT_EQ(lo.getTotalPrice(), 12395);
}

TEST(MemoryHandlerTest, initialization_readConfig_and_path_getters)
{
    std::string folderName = "memoryHandlerTestFiles";
    MemoryHandler mh(folderName);

    std::filesystem::path(mh.getWaitersPath()).filename();

    ASSERT_EQ(std::filesystem::path(mh.getWaitersPath()).filename(), "waiters.csv");
    ASSERT_EQ(std::filesystem::path(mh.getTablesPath()).filename(), "tables.csv");
    ASSERT_EQ(std::filesystem::path(mh.getDishesPath()).filename(), "dishes.csv");
    ASSERT_EQ(std::filesystem::path(mh.getBeveragesPath()).filename(), "beverages.csv");
}

TEST(MemoryHandlerTest, version_getters_and_setters)
{
    std::string folderName = "memoryHandlerTestFiles";
    MemoryHandler mh(folderName);

    std::string v1 = "1.1.1";
    mh.setWaitersVersion(v1);
    ASSERT_EQ(mh.getWaitersVersion(), v1);

    std::string v2 = "2.2.2";
    mh.setTablesVersion(v2);
    ASSERT_EQ(mh.getTablesVersion(), v2);

    std::string v3 = "3.3.3";
    mh.setDishesVersion(v3);
    ASSERT_EQ(mh.getDishesVersion(), v3);

    std::string v4 = "4.4.4";
    mh.setBeveragesVersion(v4);
    ASSERT_EQ(mh.getBeveragesVersion(), v4);
}

TEST(MemoryHandlerTest, fetchMenu)
{
    std::string folderName = "memoryHandlerTestFiles";
    MemoryHandler mh(folderName);
    Menu menu = mh.fetchMenu();

    ASSERT_FALSE(menu.empty());

    Dish *mi = dynamic_cast<Dish *>(menu.menuItems[0].get());
    ASSERT_EQ(mi->name, "Caesar Salad");
    ASSERT_EQ(mi->description, "A classic salad with romaine lettuce and Caesar dressing");
    ASSERT_EQ(mi->category, 14);
    ASSERT_EQ(mi->price, 1200);
    ASSERT_EQ(mi->ingredients, "Romaine Lettuce Caesar Dressing Parmesan Croutons");
    ASSERT_EQ(mi->volume, 350);

    mi = dynamic_cast<Dish *>(menu.menuItems[1].get());
    ASSERT_EQ(mi->name, "Tomato Soup");
    ASSERT_EQ(mi->description, "A creamy tomato soup");
    ASSERT_EQ(mi->category, 13);
    ASSERT_EQ(mi->price, 700);
    ASSERT_EQ(mi->ingredients, "Tomatoes Cream Garlic Basil");
    ASSERT_EQ(mi->volume, 300);

    Beverage *b = dynamic_cast<Beverage *>(menu.menuItems[2].get());
    ASSERT_EQ(b->name, "Margarita");
    ASSERT_EQ(b->description, "A refreshing cocktail with lime juice and tequila");
    ASSERT_EQ(b->category, 0);
    ASSERT_EQ(b->price, 850);
    ASSERT_EQ(b->alcoholPercentage, 40);
    ASSERT_EQ(b->volume, 250);

    b = dynamic_cast<Beverage *>(menu.menuItems[3].get());
    ASSERT_EQ(b->name, "Red Wine");
    ASSERT_EQ(b->description, "Full-bodied red wine with notes of cherry and oak");
    ASSERT_EQ(b->category, 5);
    ASSERT_EQ(b->price, 2500);
    ASSERT_EQ(b->alcoholPercentage, 14);
    ASSERT_EQ(b->volume, 750);
}
TEST(MemoryHandlerTest, Waiteres)
{
    std::string folderName = "memoryHandlerTestFiles";
    MemoryHandler mh(folderName);
    std::vector<Waiter> waiters = mh.fetchWaiters();

    ASSERT_FALSE(waiters.empty());

    ASSERT_EQ(waiters[0].id, 1);
    ASSERT_EQ(waiters[0].name, "John");
    ASSERT_EQ(waiters[0].surname, "Travolta");
    ASSERT_EQ(waiters[1].id, 2);
    ASSERT_EQ(waiters[1].name, "Jorek");
    ASSERT_EQ(waiters[1].surname, "Ogorek");
}

TEST(MemoryHandlerTest, Tables)
{
    std::string folderName = "memoryHandlerTestFiles";
    MemoryHandler mh(folderName);
    std::vector<Table> tables = mh.fetchTables();

    ASSERT_FALSE(tables.empty());

    ASSERT_EQ(tables[0].position.x, 1);
    ASSERT_EQ(tables[0].position.y, 2);
    ASSERT_EQ(tables[0].position.level, 3);
    ASSERT_EQ(tables[0].seats, 4);
    ASSERT_EQ(tables[1].position.x, 5);
    ASSERT_EQ(tables[1].position.y, 6);
    ASSERT_EQ(tables[1].position.level, 7);
    ASSERT_EQ(tables[1].seats, 8);
}

TEST(Employee, init)
{
    unsigned int id = 4;
    std::string name("n");
    std::string surname("s");

    Employee e(id, name, surname);

    ASSERT_EQ(e.id, id);
    ASSERT_EQ(e.name, name);
    ASSERT_EQ(e.surname, surname);
}

TEST(Employee, to_string)
{
    unsigned int id = 4;
    std::string name("n");
    std::string surname("s");

    Employee e(id, name, surname);
    ASSERT_EQ(e.toString(), "4. n s");
}

TEST(WaiterTest, init)
{
    unsigned int id = 4;
    std::string name("n");
    std::string surname("s");

    Waiter e(id, name, surname);

    ASSERT_EQ(e.id, id);
    ASSERT_EQ(e.name, name);
    ASSERT_EQ(e.surname, surname);
    ASSERT_EQ(e.toString(), "4. n s");
}

TEST(RestaurantTest, iteration_over_Waiters_typical)
{
    Restaurant restaurant;

    auto waiter_it = restaurant.wtbegin();
    ASSERT_EQ((*waiter_it).name, "John");
    ASSERT_EQ((*++waiter_it).name, "Jorek");
    ASSERT_EQ((*++waiter_it).name, "Michael");
    ASSERT_EQ((*++waiter_it).name, "Emily");
    ASSERT_EQ(++waiter_it != restaurant.wtend(), false);
}

TEST(RestaurantTest, iteration_over_Tables_typical)
{
    Restaurant restaurant;

    auto table_it = restaurant.tbbegin();
    ASSERT_EQ((*table_it).position.x, 1);
    ASSERT_EQ((*table_it).position.y, 1);
    ASSERT_EQ((*table_it).position.level, 0);
    ASSERT_EQ((*table_it).seats, 4);
    ASSERT_EQ((*++table_it).position.y, 5);
    ASSERT_EQ((*++table_it).position.y, 1);
    ASSERT_EQ((*++table_it).position.y, 5);
    ASSERT_EQ(++table_it != restaurant.tbend(), false);
}

TEST(RestaurantTest, newLocalOrder_typical)
{
    Restaurant restaurant;
    Table tbl1(Table::Position(0, 0, 0), 4);
    Table tbl2(Table::Position(5, 5, 0), 6);
    Beverage woda("Woda", "Woda mineralna niegazowana", MenuItem::beverage, 299, 0, 500);
    Waiter& wt = *(restaurant.wtbegin());

    auto &lo = restaurant.newLocalOrder(wt, tbl1);
    auto &lo2 = restaurant.newLocalOrder(wt, tbl2);

    lo.addOrderItem(woda, 1);

    LocalOrder& od = *wt.lobegin();
    OrderItem& oi = *od.oibegin();

    ASSERT_EQ(oi.menuItem.name, "Woda");
    ASSERT_EQ(lo.getStatus(), OrderStatus::inProgress);
    ASSERT_EQ(lo.table.seats, 4);
    ASSERT_EQ(lo2.table.seats, 6);
    ASSERT_EQ(tbl1.isOccupied(), true);
    ASSERT_EQ(tbl2.isOccupied(), true);
    ASSERT_EQ(tbl1.getOrder().getStatus(), OrderStatus::inProgress);
    oi.changeStatus(ItemStatus::canceled);
    lo.setClosed();
    ASSERT_EQ(tbl1.isOccupied(), false);
    EXPECT_THROW(tbl1.getOrder(), std::runtime_error);
}

TEST(RestaurantTest, newRemoteOrder_typical)
{
    Restaurant restaurant;
    Address adr("Olsztyn", "10-555", "Baltycka", "4", "Klatka H6");
    Remote remote("Elzbieta Kopyto", "123456789", adr);
    Waiter& wt = *(restaurant.wtbegin());

    auto &ro = restaurant.newRemoteOrder(wt, remote);

    ASSERT_EQ(ro.getStatus(), OrderStatus::inProgress);
    ro.setClosed();
    ASSERT_EQ(ro.getStatus(), OrderStatus::closed);

    ASSERT_EQ((*wt.rtbegin()).getStatus(), OrderStatus::closed);
}

TEST(RestaurantTest, iteration_over_LocalOrders)
{
    Restaurant restaurant;

    Address adr("Olsztyn", "10-555", "Baltycka", "4", "Klatka H6");
    Remote rmt1("Elzbieta Kopyto", "123456789", adr);
    Remote rmt2("Barbara Nara", "987654321", adr);
    Table tbl1(Table::Position(0, 0, 0), 4);
    Table tbl2(Table::Position(5, 5, 0), 6);

    restaurant.newLocalOrder(*(restaurant.wtbegin()), tbl1);
    restaurant.newRemoteOrder(*(restaurant.wtbegin()), rmt1);
    restaurant.newLocalOrder(*(restaurant.wtbegin()), tbl2);
    restaurant.newRemoteOrder(*(restaurant.wtbegin()), rmt2);

    auto loit = restaurant.lobegin();

    ASSERT_EQ((*loit).table.seats, 4);
    ASSERT_EQ((*++loit).table.seats, 6);
    ASSERT_EQ(++loit != restaurant.loend(), false);
}

TEST(RestaurantTest, iteration_over_LocalOrders_first_remote)
{
    Restaurant restaurant;

    Address adr("Olsztyn", "10-555", "Baltycka", "4", "Klatka H6");
    Remote rmt1("Elzbieta Kopyto", "123456789", adr);
    Remote rmt2("Barbara Nara", "987654321", adr);
    Table tbl1(Table::Position(0, 0, 0), 4);
    Table tbl2(Table::Position(5, 5, 0), 6);
    Waiter& wt1 = *restaurant.wtbegin();

    restaurant.newRemoteOrder(wt1, rmt1);
    restaurant.newRemoteOrder(wt1, rmt2);
    restaurant.newLocalOrder(wt1, tbl1);
    restaurant.newLocalOrder(wt1, tbl2);

    auto loit = restaurant.lobegin();

    ASSERT_EQ((*loit).table.seats, 4);
    ASSERT_EQ((*++loit).table.seats, 6);
    ASSERT_EQ(++loit != restaurant.loend(), false);
}

TEST(RestaurantTest, iteration_over_LocalOrders_empty)
{
    Restaurant restaurant;

    Address adr("Olsztyn", "10-555", "Baltycka", "4", "Klatka H6");
    Remote rmt1("Elzbieta Kopyto", "123456789", adr);
    Remote rmt2("Barbara Nara", "987654321", adr);
    Table tbl1(Table::Position(0, 0, 0), 4);
    Table tbl2(Table::Position(5, 5, 0), 6);
    Waiter& wt1 = *restaurant.wtbegin();

    restaurant.newRemoteOrder(wt1, rmt1);
    restaurant.newRemoteOrder(wt1, rmt2);

    auto loit = restaurant.lobegin();

    ASSERT_EQ(loit != restaurant.loend(), false);
}

TEST(RestaurantTest, iteration_over_LocalOrders_inprogress_typical)
{
    Restaurant restaurant;

    Address adr("Olsztyn", "10-555", "Baltycka", "4", "Klatka H6");
    Remote rmt1("Elzbieta Kopyto", "123456789", adr);
    Remote rmt2("Barbara Nara", "987654321", adr);
    Table tbl1(Table::Position(0, 0, 0), 4);
    Table tbl2(Table::Position(5, 5, 0), 6);
    Table tbl3(Table::Position(5, 10, 0), 8);
    Waiter& wt1 = *restaurant.wtbegin();

    restaurant.newLocalOrder(wt1, tbl1);
    restaurant.newRemoteOrder(wt1, rmt1);
    restaurant.newRemoteOrder(wt1, rmt2);
    auto& lo2 = restaurant.newLocalOrder(wt1, tbl2);
    restaurant.newLocalOrder(wt1, tbl3);

    lo2.setClosed();

    ASSERT_EQ(restaurant.openLocalOrdersCount(), 2);

    auto loit = restaurant.lobegin_inprogress();

    ASSERT_EQ((*loit).table.seats, 4);
    ASSERT_EQ((*++loit).table.seats, 8);
    ASSERT_EQ(++loit != restaurant.loend(), false);
}

TEST(RestaurantTest, iteration_over_RemoteOrders)
{
    Restaurant restaurant;

    Address adr("Olsztyn", "10-555", "Baltycka", "4", "Klatka H6");
    Remote rmt1("Elzbieta Kopyto", "123456789", adr);
    Remote rmt2("Barbara Nara", "987654321", adr);
    Table tbl1(Table::Position(0, 0, 0), 4);
    Table tbl2(Table::Position(5, 5, 0), 6);
    Waiter& wt1 = *restaurant.wtbegin();

    restaurant.newLocalOrder(wt1, tbl1);
    restaurant.newRemoteOrder(wt1, rmt1);
    restaurant.newLocalOrder(wt1, tbl2);
    restaurant.newRemoteOrder(wt1, rmt2);

    auto rtit = restaurant.rtbegin();

    ASSERT_EQ((*rtit).getDestination().name, "Elzbieta Kopyto");
    ASSERT_EQ((*++rtit).getDestination().name, "Barbara Nara");
    ASSERT_EQ(++rtit != restaurant.rtend(), false);
}

TEST(RestaurantTest, iteration_over_RemoteOrders_inprogress_and_count)
{
    Restaurant restaurant;

    Address adr("Olsztyn", "10-555", "Baltycka", "4", "Klatka H6");
    Remote rmt1("Elzbieta Kopyto", "123456789", adr);
    Remote rmt2("Barbara Nara", "987654321", adr);
    Remote rmt3("Anna Nara", "987654321", adr);
    Table tbl1(Table::Position(0, 0, 0), 4);
    Table tbl2(Table::Position(5, 5, 0), 6);
    Waiter& wt1 = *restaurant.wtbegin();

    restaurant.newRemoteOrder(wt1, rmt1);
    restaurant.newLocalOrder(wt1, tbl1);
    restaurant.newLocalOrder(wt1, tbl2);
    auto& ro = restaurant.newRemoteOrder(wt1, rmt2);
    restaurant.newRemoteOrder(wt1, rmt3);

    ro.setClosed();

    ASSERT_EQ(restaurant.openLocalOrdersCount(), 2);

    auto rtit = restaurant.rtbegin_inprogress();

    ASSERT_EQ((*rtit).getDestination().name, "Elzbieta Kopyto");
    ASSERT_EQ((*++rtit).getDestination().name, "Anna Nara");
    ASSERT_EQ(++rtit != restaurant.rtend(), false);
}

TEST(RestaurantTest, iteration_over_RemoteOrders_first_remote)
{
    Restaurant restaurant;

    Address adr("Olsztyn", "10-555", "Baltycka", "4", "Klatka H6");
    Remote rmt1("Elzbieta Kopyto", "123456789", adr);
    Remote rmt2("Barbara Nara", "987654321", adr);
    Table tbl1(Table::Position(0, 0, 0), 4);
    Table tbl2(Table::Position(5, 5, 0), 6);
    Waiter& wt1 = *restaurant.wtbegin();

    restaurant.newLocalOrder(wt1, tbl1);
    restaurant.newRemoteOrder(wt1, rmt1);
    restaurant.newLocalOrder(wt1, tbl2);
    restaurant.newRemoteOrder(wt1, rmt2);

    auto rtit = restaurant.rtbegin();

    ASSERT_EQ((*rtit).getDestination().name, "Elzbieta Kopyto");
    ASSERT_EQ((*++rtit).getDestination().name, "Barbara Nara");
    ASSERT_EQ(++rtit != restaurant.rtend(), false);
}

TEST(RestaurantTest, iteration_over_RemoteOrders_empty)
{
    Restaurant restaurant;

    Address adr("Olsztyn", "10-555", "Baltycka", "4", "Klatka H6");
    Remote rmt1("Elzbieta Kopyto", "123456789", adr);
    Remote rmt2("Barbara Nara", "987654321", adr);
    Table tbl1(Table::Position(0, 0, 0), 4);
    Table tbl2(Table::Position(5, 5, 0), 6);
    Waiter& wt1 = *restaurant.wtbegin();

    restaurant.newLocalOrder(wt1, tbl1);
    restaurant.newLocalOrder(wt1, tbl2);

    auto rtit = restaurant.rtbegin();

    ASSERT_EQ(rtit != restaurant.rtend(), false);
}

TEST(RestaurantTest, close_typical)
{
    Restaurant restaurant;

    Address adr("Olsztyn", "10-555", "Baltycka", "4", "Klatka H6");
    Remote rmt1("Elzbieta Kopyto", "123456789", adr);
    Table tbl1(Table::Position(0, 0, 0), 4);
    Waiter& wt1 = *restaurant.wtbegin();

    auto& ro = restaurant.newRemoteOrder(wt1, rmt1);
    auto& lo = restaurant.newLocalOrder(wt1, tbl1);

    ASSERT_EQ(restaurant.canBeClosed(), false);
    EXPECT_THROW(restaurant.close(), std::runtime_error);
    ro.setClosed();
    ASSERT_EQ(restaurant.canBeClosed(), false);
    EXPECT_THROW(restaurant.close(), std::runtime_error);
    lo.setClosed();
    ASSERT_EQ(restaurant.canBeClosed(), true);
    restaurant.close();
}

TEST(OrderTest, getWaitingTimeStr_one_min)
{
    Table tbl(Table::Position(3, 5, 0), 4);
    LocalOrder lo(tbl);
    Order& ord = lo;

    sleep(61);
    ASSERT_EQ(ord.getWaitingTimeStr(), "1 m ago");
}
