#pragma once

#include <string>

enum class UNIT
{
    g,
    ml,
    piece
};

struct MenuItem
{
    const std::string name;
    const std::string description;
    const unsigned int price;
    const unsigned int volume;
    const UNIT unit;

    MenuItem(const std::string &name, const std::string &description, unsigned int price, unsigned int volume, UNIT unit)
        : name(name), description(description), price(price), volume(volume), unit(unit)
    {
    }

    virtual MenuItem &get() = 0;
    unsigned int calories() { return 100; } // calculate calories based on ingredients
    virtual ~MenuItem() = default;
};

struct Dish : public MenuItem
{
    const std::string ingredients;

    Dish(const std::string &name, const std::string &description, unsigned int price, const std::string &ingredients, unsigned int volume)
        : MenuItem{name, description, price, volume, UNIT::g}, ingredients{ingredients}
    {
    }
    MenuItem &get() override { return *this; }
};

struct Beverage : public MenuItem
{
    const unsigned int alcoholPercentage; // in percent

    Beverage(const std::string &name, const std::string &description, unsigned int price, unsigned int alcoholPercentage, unsigned int volume)
        : MenuItem{name, description, price, volume, UNIT::ml}, alcoholPercentage{alcoholPercentage}
    {
    }
    MenuItem &get() override { return *this; }
};