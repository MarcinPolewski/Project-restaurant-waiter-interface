#pragma once

#include "menuItem.h"
#include <vector>
#include <algorithm>
#include <memory>

struct Menu
{
    const std::vector<std::unique_ptr<MenuItem>> menuItems;

    // intentionally it passed by value, because we this is the only place,
    // where objects will be hold
    Menu() = default;
    Menu(std::vector<std::unique_ptr<MenuItem>> sourceMenu) // contents of sourceMenu are moved to vector inside this classf
        : menuItems(std::move(sourceMenu))
    {
    }
};
