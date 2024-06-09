#include "waiter.h"

Waiter::LOiterator& Waiter::LOiterator::operator++()
{
    filtered_iterator::operator++();
    return *this;
}

LocalOrder& Waiter::LOiterator::operator*() const
{
    return dynamic_cast<LocalOrder&>(**this->current_it);
}

Waiter::LOiterator Waiter::lobegin()
{
    return LOiterator(orders.begin(), orders.end(),
        [](const Order* ord){return dynamic_cast<const LocalOrder*>(ord);});
}

Waiter::LOiterator Waiter::loend()
{
    return LOiterator(orders.end(), orders.end());
}

Waiter::LOiterator Waiter::lobegin_inprogress()
{
    return LOiterator(orders.begin(), orders.end(),
        [](const Order* ord){return dynamic_cast<const LocalOrder*>(ord)
            && ord->getStatus() == OrderStatus::inProgress;});
}
//new
Waiter::const_LOiterator& Waiter::const_LOiterator::operator++()
{
    const_filtered_iterator::operator++();
    return *this;
}

const LocalOrder& Waiter::const_LOiterator::operator*() const
{
    return dynamic_cast<const LocalOrder&>(**this->current_it);
}

Waiter::const_LOiterator Waiter::locbegin() const
{
    return const_LOiterator(orders.cbegin(), orders.cend(),
        [](const Order* ord){return dynamic_cast<const LocalOrder*>(ord);});
}

Waiter::const_LOiterator Waiter::locend() const
{
    return const_LOiterator(orders.end(), orders.end());
}

Waiter::const_LOiterator Waiter::locbegin_inprogress() const
{
    return const_LOiterator(orders.cbegin(), orders.cend(),
        [](const Order* ord){return dynamic_cast<const LocalOrder*>(ord)
            && ord->getStatus() == OrderStatus::inProgress;});
}

Waiter::RTiterator& Waiter::RTiterator::operator++()
{
    filtered_iterator::operator++();
    return *this;
}

RemoteOrder& Waiter::RTiterator::operator*() const
{
    return dynamic_cast<RemoteOrder&>(**this->current_it);
}

Waiter::RTiterator Waiter::rtbegin()
{
    return RTiterator(orders.begin(), orders.end(),
        [](const Order* ord){return dynamic_cast<const RemoteOrder*>(ord);});
}

Waiter::RTiterator Waiter::rtend()
{
    return RTiterator(orders.end(), orders.end());
}

Waiter::RTiterator Waiter::rtbegin_inprogress()
{
    return RTiterator(orders.begin(), orders.end(),
        [](const Order* ord){return dynamic_cast<const RemoteOrder*>(ord)
            && ord->getStatus() == OrderStatus::inProgress;});
}

Waiter::const_RTiterator& Waiter::const_RTiterator::operator++()
{
    const_filtered_iterator::operator++();
    return *this;
}

const RemoteOrder& Waiter::const_RTiterator::operator*() const
{
    return dynamic_cast<const RemoteOrder&>(**this->current_it);
}

Waiter::const_RTiterator Waiter::rtcbegin() const
{
    return const_RTiterator(orders.cbegin(), orders.cend(),
        [](const Order* ord){return dynamic_cast<const RemoteOrder*>(ord);});
}

Waiter::const_RTiterator Waiter::rtcend() const
{
    return const_RTiterator(orders.cend(), orders.cend());
}

Waiter::const_RTiterator Waiter::rtcbegin_inprogress() const
{
    return const_RTiterator(orders.cbegin(), orders.cend(),
        [](const Order* ord){return dynamic_cast<const RemoteOrder*>(ord)
            && ord->getStatus() == OrderStatus::inProgress;});
}

unsigned int Waiter::openLocalOrdersCount() const
{
    unsigned int count = 0;
    for (const_LOiterator it = this->locbegin_inprogress(); it != this->locend(); ++it)
        count++;
    return count;
}

unsigned int Waiter::openRemoteOrdersCount() const
{
    unsigned int count = 0;
    for (const_RTiterator it = this->rtcbegin_inprogress(); it != this->rtcend(); ++it)
        count++;
    return count;
}