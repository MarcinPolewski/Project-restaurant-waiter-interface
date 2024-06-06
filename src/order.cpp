#include "order.h"

void Order::addOrderItem(const MenuItem& menu_item, unsigned int count,
        const std::string& com, unsigned int discnt)
{
    if (this->orderStatus == OrderStatus::closed)
        throw (std::runtime_error("Cannot add order item - order is closed."));
    OrderItem order_item(menu_item, count, com, discnt);
    this->orderItems.push_back(order_item);
}

OrderItem& Order::operator[](unsigned int index)
{
    if (index >= this->orderItems.size())
        throw (std::invalid_argument("Index out of range."));

    return this->orderItems[index];
}

void Order::setClosed()
{
    if (this->orderStatus == OrderStatus::closed)
        throw (std::runtime_error("Cannot close order - order is already closed."));
    for (auto orderit : orderItems)
    {
        if (orderit.getStatus() != ItemStatus::delivered
            && orderit.getStatus() != ItemStatus::canceled)
            throw(std::runtime_error("Cannot close order - unclosed order items."));
    }
    this->orderStatus = OrderStatus::closed;
}

time_t Order::getWaitingTime() const
{
    if (this->orderStatus != OrderStatus::inProgress)
        throw (std::runtime_error("Cannot get waiting time - order is closed."));
    return time(NULL) - this->waitingTimeStamp;
}

void Order::resetWaitingTime()
{
    if (this->orderStatus != OrderStatus::inProgress)
        throw (std::runtime_error("Cannot reset waiting time - order is closed."));
    this->waitingTimeStamp = time(NULL);
}

unsigned int Order::getTotalPrice() const
{
    unsigned int total_price = 0;
    for (auto order_item : this->orderItems)
        if (order_item.getStatus() != ItemStatus::canceled)
            total_price += order_item.getPrice();

    return total_price;
}

Order::iterator& Order::iterator::operator++()
{
    this->it++;
    return *this;
}

LocalOrder::LocalOrder(Table& tbl)
    : table(tbl)
{
    if (tbl.isOccupied())
        throw (std::runtime_error("Cannot create order - table is occupied."));
    tbl.order = this;
}

void LocalOrder::setClosed()
{
    Order::setClosed();
    const_cast<Table&>(this->table).order = nullptr;
}