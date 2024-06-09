#pragma once

#include <vector>
#include <string>

#include "order.h"
#include "destination.h"
#include "employee.h"
#include "filtered_iterator.h"


class Waiter : public Employee
{
    std::vector<Order*> orders;

    friend class Restaurant;
public:
    using Employee::Employee; // inheriting constructors from parent

    class LOiterator : public filtered_iterator<Order>
    {
    public:
        using filtered_iterator::filtered_iterator;
        LOiterator& operator++();
        LocalOrder& operator*();
    };
    LOiterator lobegin();
    LOiterator loend();

    LOiterator lobegin_inprogress();

    class RTiterator : public filtered_iterator<Order>
    {
    public:
        using filtered_iterator::filtered_iterator;
        RTiterator& operator++();
        RemoteOrder& operator*();
    };
    RTiterator rtbegin();
    RTiterator rtend();

    RTiterator rtbegin_inprogress();

    unsigned int openLocalOrdersCount();
    unsigned int openRemoteOrdersCount();
};