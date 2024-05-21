#pragma once
#include "menuItem.h"
#include <time.h>

class OrderItem
{
public:
    enum class ItemStatus
    {
        ordered,
        inPreparation,
        readyToDeliver,
        canceled,
    };
private:
    ItemStatus itemStatus = ItemStatus::ordered;
    std::string comment;
    unsigned int discount;
public:
    const MenuItem& menuItem;
    const unsigned int quantity;
    const time_t orderTime = time(NULL);

    OrderItem(const MenuItem& menu_item, unsigned int count,
        const std::string& com = "", unsigned int discnt = 0);
    OrderItem(const OrderItem&) = delete;
    OrderItem(OrderItem&&) = delete;

    void operator=(const MenuItem&) = delete;
    void operator=(MenuItem&&) = delete;

    void add_comment(const std::string& new_comment);
    // void add_comment(std::string&& new_comment);    // TODO
    void set_discount(unsigned int new_discount);

    const std::string& get_comment() const {return this->comment;}
    unsigned int get_discount() const {return this->discount;}
};
