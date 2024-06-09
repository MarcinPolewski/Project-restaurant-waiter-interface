#include "restaurant.h"

bool Restaurant::isWaiter(const Waiter& waiter) const
{
    for (const_WTiterator it = this->wtcbegin(); it != this->wtcend(); ++it)
        if (&*it == &waiter)
            return true;
    return false;
}

bool Restaurant::isTable(const Table& table) const
{
    for (const_TBiterator it = this->tbcbegin(); it != this->tbcend(); ++it)
        if (&*it == &table)
            return true;
    return false;
}

Restaurant::Restaurant()
    : memoryHandler(),
      serverHandler(memoryHandler),
      menu(memoryHandler.fetchMenu())
{
    std::vector<Waiter> waiters_vec = memoryHandler.fetchWaiters();
    std::vector<Table> tables_vec = memoryHandler.fetchTables();

    if (menu.empty())
        throw std::runtime_error("Menu cannot be empty");
    if (waiters_vec.empty())
        throw std::runtime_error("Waiters list cannot be empty");

    for (auto&& waiter : waiters_vec)
        this->waiters.push_back(std::make_unique<Waiter>(waiter));

    for (auto&& table: tables_vec)
        this->tables.push_back(std::make_unique<Table>(table));
}

LocalOrder& Restaurant::newLocalOrder(Waiter& waiter, Table& table)
{
    if (!this->isWaiter(waiter))
        throw (std::runtime_error("Cannot create order, waiter is not in the restaurant"));
    if (!this->isTable(table))
        throw (std::runtime_error("Cannot create order, table is not in the restaurant"));
    orders.push_back(std::make_unique<LocalOrder>(table));
    waiter.orders.push_back(orders.back().get());
    return dynamic_cast<LocalOrder&>(*orders.back().get());
}

RemoteOrder& Restaurant::newRemoteOrder(Waiter& waiter, Remote& remote)
{
    if (!this->isWaiter(waiter))
        throw (std::runtime_error("Cannot create order, waiter is not in the restaurant"));
    orders.push_back(std::make_unique<RemoteOrder>(remote));
    waiter.orders.push_back(orders.back().get());
    return dynamic_cast<RemoteOrder&>(*orders.back().get());
}

const Menu& Restaurant::getMenu() const
{
    return menu;
}

Restaurant::WTiterator Restaurant::wtbegin()
{
    return WTiterator(this->waiters.begin(), this->waiters.end());
}

Restaurant::WTiterator Restaurant::wtend()
{
    return WTiterator(this->waiters.end(), this->waiters.end());
}

Restaurant::const_WTiterator Restaurant::wtcbegin() const
{
    return const_WTiterator(this->waiters.cbegin(), this->waiters.cend());
}

Restaurant::const_WTiterator Restaurant::wtcend() const
{
    return const_WTiterator(this->waiters.cend(), this->waiters.cend());
}

Restaurant::TBiterator Restaurant::tbbegin()
{
    return TBiterator(this->tables.begin(), this->tables.end());
}

Restaurant::TBiterator Restaurant::tbend()
{
    return TBiterator(this->tables.end(), this->tables.end());
}

Restaurant::const_TBiterator Restaurant::tbcbegin() const
{
    return const_TBiterator(this->tables.cbegin(), this->tables.cend());
}

Restaurant::const_TBiterator Restaurant::tbcend() const
{
    return const_TBiterator(this->tables.cend(), this->tables.cend());
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

Restaurant::LOiterator Restaurant::lobegin_inprogress()
{
    return LOiterator(this->orders.begin(), this->orders.end(),
        [](const std::unique_ptr<Order>& ord){return dynamic_cast<LocalOrder*>(ord.get())
            && ord.get()->getStatus() == OrderStatus::inProgress;});
}

Restaurant::const_LOiterator& Restaurant::const_LOiterator::operator++()
{
    const_filtered_unique_iterator::operator++();
    return *this;
}

const LocalOrder& Restaurant::const_LOiterator::operator*()
{
    return dynamic_cast<const LocalOrder&>(*(*current_it).get());
}

Restaurant::const_LOiterator Restaurant::locbegin() const
{
    return const_LOiterator(this->orders.cbegin(), this->orders.cend(),
        [](const std::unique_ptr<Order>& ord){return dynamic_cast<const LocalOrder*>(ord.get());});
}

Restaurant::const_LOiterator Restaurant::locend() const
{
    return const_LOiterator(this->orders.cend(), this->orders.cend(), nullptr);
}

Restaurant::const_LOiterator Restaurant::locbegin_inprogress() const
{
    return const_LOiterator(this->orders.cbegin(), this->orders.cend(),
        [](const std::unique_ptr<Order>& ord){return dynamic_cast<const LocalOrder*>(ord.get())
            && ord.get()->getStatus() == OrderStatus::inProgress;});
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

Restaurant::RTiterator Restaurant::rtbegin_inprogress()
{
    return RTiterator(this->orders.begin(), this->orders.end(),
        [](const std::unique_ptr<Order>& ord){return dynamic_cast<RemoteOrder*>(ord.get())
            && ord.get()->getStatus() == OrderStatus::inProgress;});
}

unsigned int Restaurant::openLocalOrdersCount() const
{
    unsigned int counter = 0;
    for (const_LOiterator it = this->locbegin_inprogress(); it != this->locend(); ++it)
        counter++;
    return counter;
}

unsigned int Restaurant::openRemoteOrdersCount()
{
    unsigned int counter = 0;
    for (RTiterator it = this->rtbegin_inprogress(); it != this->loend(); ++it)
        counter++;
    return counter;
}

bool Restaurant::canBeClosed()
{
    return !(this->openLocalOrdersCount() || this->openRemoteOrdersCount());
}

void Restaurant::close()
{
    if (!this->canBeClosed())
        throw std::runtime_error("Cannot close restaurant, some orders are still in progress");
}