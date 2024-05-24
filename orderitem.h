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
        delivered,
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

    void addComment(const std::string& new_comment);
    // void add_comment(std::string&& new_comment);    // TODO
    const std::string& getComment() const {return this->comment;}

    void setDiscount(unsigned int new_discount);
    unsigned int getDiscount() const {return this->discount;}

    void setDelivered();
    void setCancelled();
    const ItemStatus& getStatus() const {return this->itemStatus;}

    unsigned int getPrice() const {return quantity * menuItem.price;}
    time_t getWaitingTime() const {return time(NULL) - orderTime;}


};
