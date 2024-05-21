#pragma once

#include "menuItem.h"
#include <vector>
#include <algorithm>
#include <memory>

struct Menu
{
    std::vector<std::unique_ptr<MenuItem>> menuItems;

    void add(std::unique_ptr<MenuItem> menu_item)
    {
        menuItems.push_back(std::move(menu_item));
    }
};
