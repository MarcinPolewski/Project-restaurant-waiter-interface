#include "restaurant.h"

Restaurant::Restaurant()
    : memoryHandler(),
      serverHandler(memoryHandler),
      menu(memoryHandler.fetchMenu()),
      waiters(memoryHandler.fetchWaiters()),
      tables(memoryHandler.fetchTables())
{
    if (menu.empty())
        throw std::runtime_error("Menu cannot be empty");
    if (waiters.empty())
        throw std::runtime_error("Waiters list cannot be empty");

    currentWaiter = &waiters[0];
}

RemoteOrder& Restaurant::newRemoteOrder(Remote& remote)
{
    orders.push_back(std::make_unique<RemoteOrder>(remote));
    return dynamic_cast<RemoteOrder&>(*orders.back().get());
}

LocalOrder& Restaurant::newLocalOrder(Table& table)
{
    orders.push_back(std::make_unique<LocalOrder>(table));
    return dynamic_cast<LocalOrder&>(*orders.back().get());
}

void Restaurant::closeRestaurant()
{
    if (!orders.empty())
        throw std::runtime_error("cannot close restaurant, when some orders are still in progress");
}

void Restaurant::changeCurrentWaiter(Waiter *waiter)
{
    currentWaiter = waiter;
}

Waiter const *Restaurant::getCurrentWaiter() const
{
    return currentWaiter;
}

std::vector<Waiter> const &Restaurant::getWaiters() const
{
    return waiters;
}
std::vector<Table> const &Restaurant::getTables() const
{
    return tables;
}
Menu const &Restaurant::getMenu() const
{
    return menu;
}

Restaurant::LOiterator::LOiterator(u_order_iterator start_it, u_order_iterator end_it)
    : current_it(start_it), end_it(end_it)
{
    if (this->current_it != this->end_it)
        this->current_it = std::find_if(this->current_it, this->end_it,
            [](const std::unique_ptr<Order>& ord){return dynamic_cast<LocalOrder*>(ord.get());});
}

Restaurant::LOiterator& Restaurant::LOiterator::operator++()
{
    if (this->current_it != this->end_it)
    this->current_it = std::find_if(++this->current_it, this->end_it,
        [](const std::unique_ptr<Order>& ord){return dynamic_cast<LocalOrder*>(ord.get());});
    return *this;
}

LocalOrder& Restaurant::LOiterator::operator*()
{
    return dynamic_cast<LocalOrder&>(*(*current_it).get());
}

bool Restaurant::LOiterator::operator!=(const LOiterator& it2) const
{
    return this->current_it != it2.current_it;
}

Restaurant::LOiterator Restaurant::lobegin()
{
    return LOiterator(this->orders.begin(), this->orders.end());
}

Restaurant::LOiterator Restaurant::loend()
{
    return LOiterator(this->orders.end(), this->orders.end());
}