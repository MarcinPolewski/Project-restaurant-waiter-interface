#include <menuitem.h>

MenuItem::MenuItem(const std::string &name, const std::string &description,
    Category category, unsigned int price, unsigned int volume, Unit unit)
    : name(name),
      description(description),
      price(price),
      volume(volume),
      unit(unit),
      category(category)
{
}

std::string MenuItem::getPriceStr() const
{
    unsigned int mi_price = this->price;
    std::string units = std::to_string(mi_price / 100);
    std::string fraction = std::to_string(mi_price % 100);
    if (fraction.length() != 2)
        fraction = "0" + fraction;
    return units + "," + fraction;
}

std::string MenuItem::getVolumeStr() const
{
    std::string volume_str = std::to_string(this->volume);
    if (this->unit == MenuItem::Unit::g)
        return volume_str + "g";
    else if (this->unit == MenuItem::Unit::ml)
        return volume_str + "ml";
    else if (this->unit == MenuItem::Unit::piece)
        return volume_str + "pc";
    return volume_str;
}

Dish::Dish(const std::string &name, const std::string &description,
    Category category, unsigned int price, const std::string &ingredients,
    unsigned int volume, Unit unit)
    : MenuItem{name, description, category, price, volume, unit},
      ingredients{ingredients}
{
}

Dish& Dish::get()
{
    return *this;
}

Beverage::Beverage(const std::string &name, const std::string &description,
    Category category, unsigned int price, unsigned int alcoholPercentage,
    unsigned int volume, Unit unit)
    : MenuItem{name, description, category, price, volume, unit},
      alcoholPercentage{alcoholPercentage}
{
}

Beverage& Beverage::get()
{
    return *this;
}