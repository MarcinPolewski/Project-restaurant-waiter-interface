#pragma once

#include <string>

enum class UNIT
{
    kg,
    g,
    l,
    ml,
    piece
};

struct MenuItem
{
    const std::string name;
    const std::string description;
    const unsigned int price;
    const UNIT unit;

    virtual MenuItem &get() = 0;
    unsigned int calories();
    unsigned int portion();
};

struct Dish : public MenuItem
{
    const std::string ingredients;
    UNIT unit = UNIT::g;

    MenuItem &get() override { return *this; }
};

struct Beverage : public MenuItem
{
    const unsigned int volume;
    const unsigned int alcoholPercentage; // in percent
    UNIT unit = UNIT::ml;

    MenuItem &get() override { return *this; }
};