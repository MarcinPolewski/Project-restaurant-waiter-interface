#pragma once

#include "menuItem.h"
#include <vector>
#include <algorithm>
#include <memory>

struct Menu
{
    std::vector<std::unique_ptr<MenuItem>> menuItems;

    // intentionally it passed by value, because we this is the only place,
    // where objects will be hold
    void add(std::unique_ptr<MenuItem> menu_item)
    {
        menuItems.push_back(std::move(menu_item));
    }
};
