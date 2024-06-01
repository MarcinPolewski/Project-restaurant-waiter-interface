#include "order.h"

OrderItem& Order::addOrderItem(const MenuItem& menu_item, unsigned int count,
        const std::string& com, unsigned int discnt)
{
    OrderItem order_item(menu_item, count, com, discnt);
    this->orderItems.push_back(order_item);

    return this->orderItems.back();
}

OrderItem& Order::operator[](unsigned int index)
{
    if (index >= this->orderItems.size())
        throw (std::invalid_argument("Index out of range."));

    return this->orderItems[index];
}

unsigned int Order::getTotalPrice() const
{
    unsigned int total_price = 0;
    for (auto order_item : this->orderItems)
        total_price += order_item.getPrice();

    return total_price;
}

Order::iterator& Order::iterator::operator++()
{
    this->it++;
    return *this;
}