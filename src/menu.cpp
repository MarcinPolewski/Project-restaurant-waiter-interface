#include "menu.h"

Menu::Menu(std::vector<std::unique_ptr<MenuItem>>&& sourceMenu)
        : menuItems(std::move(sourceMenu))
{
}

Menu::MIiterator Menu::mibegin() const
{
    return MIiterator(this->menuItems.begin(), this->menuItems.end());
}

Menu::MIiterator Menu::miend() const
{
    return MIiterator(this->menuItems.end(), this->menuItems.end());
}

unsigned int Menu::size() const
{
    return this->menuItems.size();
}

bool Menu::empty() const
{
    return menuItems.empty();
}