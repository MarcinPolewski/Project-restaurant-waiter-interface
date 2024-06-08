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
        [](Order* ord){return dynamic_cast<LocalOrder*>(ord);});
}

Waiter::LOiterator Waiter::loend()
{
    return LOiterator(orders.begin(), orders.end(), nullptr);
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
        [](Order* ord){return dynamic_cast<RemoteOrder*>(ord);});
}

Waiter::RTiterator Waiter::rtend()
{
    return RTiterator(orders.begin(), orders.end(), nullptr);
}