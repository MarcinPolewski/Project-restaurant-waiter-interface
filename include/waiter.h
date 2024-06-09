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
        LocalOrder& operator*() const;
    };
    LOiterator lobegin();
    LOiterator loend();

    LOiterator lobegin_inprogress();

    class const_LOiterator : public const_filtered_iterator<Order>
    {
    public:
        using const_filtered_iterator::const_filtered_iterator;
        const_LOiterator& operator++();
        const LocalOrder& operator*() const;
    };
    const_LOiterator locbegin() const;
    const_LOiterator locend() const;

    const_LOiterator locbegin_inprogress() const;

    class RTiterator : public filtered_iterator<Order>
    {
    public:
        using filtered_iterator::filtered_iterator;
        RTiterator& operator++();
        RemoteOrder& operator*() const;
    };
    RTiterator rtbegin();
    RTiterator rtend();

    RTiterator rtbegin_inprogress();

    class const_RTiterator : public const_filtered_iterator<Order>
    {
    public:
        using const_filtered_iterator::const_filtered_iterator;
        const_RTiterator& operator++();
        const RemoteOrder& operator*() const;
    };
    const_RTiterator rtcbegin() const;
    const_RTiterator rtcend() const;

    const_RTiterator rtcbegin_inprogress() const;

    unsigned int openLocalOrdersCount() const;
    unsigned int openRemoteOrdersCount() const;
};