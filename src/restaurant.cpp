#include "restaurant.h"

Restaurant::Restaurant()
    : memoryHandler(),
      serverHandler(memoryHandler),
      menu(memoryHandler.fetchMenu()),
      tables(memoryHandler.fetchTables())
{
    std::vector<Waiter> waiters_vec = memoryHandler.fetchWaiters();

    if (menu.empty())
        throw std::runtime_error("Menu cannot be empty");
    if (waiters_vec.empty())
        throw std::runtime_error("Waiters list cannot be empty");

    for (auto&& waiter : waiters_vec)
        this->waiters.push_back(std::make_unique<Waiter>(waiter));
}

RemoteOrder& Restaurant::newRemoteOrder(Waiter& waiter, Remote& remote)
{
    orders.push_back(std::make_unique<RemoteOrder>(remote));
    waiter.orders.push_back(orders.back().get());
    return dynamic_cast<RemoteOrder&>(*orders.back().get());
}

LocalOrder& Restaurant::newLocalOrder(Waiter& waiter, Table& table)
{
    orders.push_back(std::make_unique<LocalOrder>(table));
    waiter.orders.push_back(orders.back().get());
    return dynamic_cast<LocalOrder&>(*orders.back().get());
}

void Restaurant::closeRestaurant()
{
    if (!orders.empty())
        throw std::runtime_error("cannot close restaurant, when some orders are still in progress");
}

Restaurant::WTiterator Restaurant::wtbegin()
{
    return WTiterator(this->waiters.begin(), this->waiters.end());
}

Restaurant::WTiterator Restaurant::wtend()
{
    return WTiterator(this->waiters.end(), this->waiters.end());
}

std::vector<Table> const &Restaurant::getTables() const
{
    return tables;
}
Menu const &Restaurant::getMenu() const
{
    return menu;
}

Restaurant::LOiterator& Restaurant::LOiterator::operator++()
{
    filtered_unique_iterator::operator++();
    return *this;
}

LocalOrder& Restaurant::LOiterator::operator*()
{
    return dynamic_cast<LocalOrder&>(*(*current_it).get());
}

Restaurant::LOiterator Restaurant::lobegin()
{
    return LOiterator(this->orders.begin(), this->orders.end(),
        [](const std::unique_ptr<Order>& ord){return dynamic_cast<LocalOrder*>(ord.get());});
}

Restaurant::LOiterator Restaurant::loend()
{
    return LOiterator(this->orders.end(), this->orders.end(), nullptr);
}

Restaurant::RTiterator& Restaurant::RTiterator::operator++()
{
    filtered_unique_iterator::operator++();
    return *this;
}

RemoteOrder& Restaurant::RTiterator::operator*()
{
    return dynamic_cast<RemoteOrder&>(*(*this->current_it).get());
}

Restaurant::RTiterator Restaurant::rtbegin()
{
    return RTiterator(this->orders.begin(), this->orders.end(),
        [](const std::unique_ptr<Order>& ord){return dynamic_cast<RemoteOrder*>(ord.get());});
}

Restaurant::RTiterator Restaurant::rtend()
{
    return RTiterator(this->orders.end(), this->orders.end(), nullptr);
}