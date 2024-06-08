#include "order.h"

void Order::addOrderItem(const MenuItem& menu_item, unsigned int count,
        const std::string& com, unsigned int discnt)
{
    if (this->orderStatus == OrderStatus::closed)
        throw (std::runtime_error("Cannot add order item - order is closed."));
    this->orderItems.push_back(std::make_unique<OrderItem>(menu_item, count, com, discnt));
}

OrderItem& Order::operator[](unsigned int index)
{
    if (index >= this->orderItems.size())
        throw (std::invalid_argument("Index out of range."));

    return *this->orderItems[index].get();
}

OrderStatus Order::getStatus() const
{
    return orderStatus;
}

void Order::setClosed()
{
    if (this->orderStatus == OrderStatus::closed)
        throw (std::runtime_error("Cannot close order - order is already closed."));
    for (auto& orderit : orderItems)
    {
        if (orderit->getStatus() != ItemStatus::delivered
            && orderit->getStatus() != ItemStatus::canceled)
            throw(std::runtime_error("Cannot close order - unclosed order items."));
    }
    this->orderStatus = OrderStatus::closed;
}

time_t Order::getOrderTime() const
{
    return this->orderTime;
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
    for (auto& order_item : this->orderItems)
        if (order_item->getStatus() != ItemStatus::canceled)
            total_price += order_item->getPrice();

    return total_price;
}

Order::OIiterator Order::oibegin()
{
    return OIiterator(orderItems.begin(), orderItems.end());
}

Order::OIiterator Order::oiend()
{
    return OIiterator(orderItems.end(), orderItems.end());
}

std::string Order::getOrderTimeStr() const
{
    char buf[6];
    strftime(buf, 6, "%H:%M", localtime(&this->orderTime));
    return std::string(buf);
}

std::string Order::getWaitingTimeStr() const
{
    time_t waiting_time = this->getWaitingTime();

    if (waiting_time / 60 == 0)
        return "now";
    else
        return std::to_string(waiting_time / 60) + " m ago";
}

std::string Order::getTotalPriceStr() const
{
    unsigned int total_price = this->getTotalPrice();
    std::string units = std::to_string(total_price / 100);
    std::string fraction = std::to_string(total_price % 100);
    if (fraction.length() != 2)
        fraction = "0" + fraction;
    return units + "," + fraction;
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