#pragma once

#include "menuitem.h"
#include "filtered_unique_iterator.h"

#include <vector>
#include <algorithm>
#include <memory>

struct Menu
{
    const std::vector<std::unique_ptr<MenuItem>> menuItems;

    Menu() = default;
    Menu(std::vector<std::unique_ptr<MenuItem>>&& sourceMenu);

    typedef const_filtered_unique_iterator<MenuItem> MIiterator;
    MIiterator mibegin() const;
    MIiterator miend() const;

    unsigned int size() const;
    bool empty() const;
};
