#pragma once

#include <string>

struct MenuItem
{
    enum class UNIT
    {
        g,
        ml,
        piece
    };

    const std::string name;
    const std::string description;
    const unsigned int price;
    const unsigned int volume;
    const UNIT unit;

    MenuItem(const std::string &name, const std::string &description, unsigned int price, unsigned int volume, UNIT unit)
        : name(name), description(description), price(price), volume(volume), unit(unit)
    {
    }

    virtual std::unique_ptr<MenuItem> get() = 0;
    virtual ~MenuItem() = default;
};

struct Dish : public MenuItem
{
    enum class CATEGORY
    {
        starter,
        soup,
        salad,
        mainCourse,
        fish,
        pizza,
        burger,
        desert
    };

    const Dish::CATEGORY category;
    const std::string ingredients;

    Dish(const std::string &name, const std::string &description, Dish::CATEGORY category, unsigned int price, const std::string &ingredients, unsigned int volume, UNIT unit = UNIT::g)
        : MenuItem{name, description, price, volume, unit}, category(category), ingredients{ingredients}
    {
    }


    std::unique_ptr<MenuItem> get() override {return std::make_unique<Dish>(*this);}
};

struct Beverage : public MenuItem
{
    enum class CATEGORY
    {
        beverage,
        coldBeverage,
        hotBeverage,
        wine,
        whiteWine,
        redWine,
        whiskey,
        vodka,
        smoothie
    };

    const Beverage::CATEGORY category;
    const unsigned int alcoholPercentage;

     Beverage(const std::string &name, const std::string &description, Beverage::CATEGORY category, unsigned int price, unsigned int volume,  UNIT unit = UNIT::ml, unsigned int alcoholPercentage = 0)
        : MenuItem{name, description, price, volume, unit}, category(category), alcoholPercentage(alcoholPercentage)
    {
    }

    std::unique_ptr<MenuItem> get() override {return std::make_unique<Beverage>(*this);}
};