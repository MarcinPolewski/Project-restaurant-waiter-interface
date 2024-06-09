#pragma once

#include <string>

struct MenuItem
{
    enum Unit
    {
        g,
        ml,
        piece
    };

    enum Category
    {
        beverage,
        coldBeverage,
        hotBeverage,
        wine,
        whiteWine,
        redWine,
        pinkWine,
        whiskey,
        vodka,
        drink,
        beer,
        smoothie,
        starter,
        soup,
        salad,
        mainCourse,
        fish,
        pizza,
        burger,
        desert
    };

    const std::string name;
    const std::string description;
    const unsigned int price;
    const unsigned int volume;
    const Unit unit;
    const Category category;

    MenuItem(const std::string &name, const std::string &description,
        Category category, unsigned int price, unsigned int volume, Unit unit);

    virtual MenuItem &get() = 0;
    virtual ~MenuItem() = default;

    std::string getPriceStr() const;
    std::string getVolumeStr() const;
};

struct Dish : public MenuItem
{
    const std::string ingredients;

    Dish(const std::string &name, const std::string &description,
        Category category, unsigned int price, const std::string &ingredients,
        unsigned int volume, Unit unit = Unit::g);

    Dish& get() override;
};

struct Beverage : public MenuItem
{
    const unsigned int alcoholPercentage;

    Beverage(const std::string &name, const std::string &description,
        Category category, unsigned int price, unsigned int alcoholPercentage,
        unsigned int volume, Unit unit = Unit::ml);

    Beverage& get() override;
};