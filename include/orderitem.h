#pragma once

#include "menuitem.h"

#include <time.h>

enum class ItemStatus
{
    created,
    ordered,
    inPreparation,
    readyToDeliver,
    delivered,
    canceled,
};

class OrderItem
{
private:

    ItemStatus itemStatus = ItemStatus::created;
    std::string comment;
    unsigned int discount;
public:
    const MenuItem& menuItem;
    const unsigned int quantity;
    const time_t orderTime = time(NULL);

    OrderItem(const MenuItem& menu_item, unsigned int count,
        const std::string& com = "", unsigned int discnt = 0);

    void addComment(const std::string& new_comment);
    const std::string& getComment() const {return this->comment;}

    void setDiscount(unsigned int new_discount);
    unsigned int getDiscount() const {return this->discount;}

    void changeStatus(ItemStatus new_status);
    void setOrdered();
    void setDelivered();
    void setCancelled();
    ItemStatus getStatus() const{return this->itemStatus;}

    unsigned int getPrice() const;
    time_t getWaitingTime() const {return time(NULL) - orderTime;}
};
