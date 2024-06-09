#include "waiter.h"

Waiter::LOiterator& Waiter::LOiterator::operator++()
{
    filtered_iterator::operator++();
    return *this;
}

LocalOrder& Waiter::LOiterator::operator*()
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
    return LOiterator(orders.end(), orders.end(), nullptr);
}

Waiter::LOiterator Waiter::lobegin_inprogress()
{
    return LOiterator(orders.begin(), orders.end(),
        [](const Order* ord){return dynamic_cast<const LocalOrder*>(ord)
            && ord->getStatus() == OrderStatus::inProgress;});
}

Waiter::RTiterator& Waiter::RTiterator::operator++()
{
    filtered_iterator::operator++();
    return *this;
}

RemoteOrder& Waiter::RTiterator::operator*()
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
    return RTiterator(orders.end(), orders.end(), nullptr);
}

Waiter::RTiterator Waiter::rtbegin_inprogress()
{
    return RTiterator(orders.begin(), orders.end(),
        [](const Order* ord){return dynamic_cast<const RemoteOrder*>(ord)
            && ord->getStatus() == OrderStatus::inProgress;});
}

unsigned int Waiter::openLocalOrdersCount()
{
    unsigned int count = 0;
    for (LOiterator it = this->lobegin_inprogress(); it != this->loend(); ++it)
        count++;
    return count;
}

unsigned int Waiter::openRemoteOrdersCount()
{
    unsigned int count = 0;
    for (RTiterator it = this->rtbegin_inprogress(); it != this->rtend(); ++it)
        count++;
    return count;
}