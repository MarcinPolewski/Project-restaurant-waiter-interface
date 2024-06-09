#pragma once

#include "menuitem.h"

#include <time.h>
#include <iostream>

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
    const std::string& getComment() const;

    void setDiscount(unsigned int new_discount);
    unsigned int getDiscount() const;

    void changeStatus(ItemStatus new_status);
    void setOrdered();
    void setInPreparation();
    void setReadyToDeliver();
    void setDelivered();
    void setCancelled();
    ItemStatus getStatus() const;

    unsigned int getPrice() const;

    time_t getWaitingTime() const;

    std::string getPriceStr() const;
    std::string getQuantityStr() const;
    std::string getStatusStr() const;
    std::string getDiscountStr() const;
};