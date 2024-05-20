#pragma once

#include "menuItem.h"
#include <vector>

struct Menu
{
    const std::vector<Beverage> beverages;
    const std::vector<Dish> dishes;

    // intentionally it passed by value, because we this is the only place,
    // where objects will be hold
    Menu(const std::vector<Beverage> beverages, const std::vector<Dish> dishes)
        : beverages(beverages), dishes(dishes)
    {
    }
};
