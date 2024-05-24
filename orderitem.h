#pragma once

#include "menuitem.h"

#include <time.h>

class WaiterOrderItem
{
public:
    virtual void addComment(const std::string&) = 0;
    virtual const std::string& getComment() const = 0;
    virtual void setDiscount(unsigned int) = 0;
    virtual unsigned int getDiscount() const = 0;
    virtual void setDelivered() = 0;
    virtual void setCancelled() = 0;
    virtual unsigned int getPrice() const = 0;
    virtual time_t getWaitingTime() const = 0;

    enum class ItemStatus
    {
        ordered,
        inPreparation,
        readyToDeliver,
        delivered,
        canceled,
    };

    virtual ItemStatus getStatus() const = 0;
};

class OrderItem : public WaiterOrderItem
{
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

    void addComment(const std::string& new_comment) override;
    // void add_comment(std::string&& new_comment);    // TODO
    const std::string& getComment() const override {return this->comment;}

    void setDiscount(unsigned int new_discount) override;
    unsigned int getDiscount() const override {return this->discount;}

    void setDelivered() override;
    void setCancelled() override;
    ItemStatus getStatus() const override {return this->itemStatus;}

    unsigned int getPrice() const override {return quantity * menuItem.price;}
    time_t getWaitingTime() const override {return time(NULL) - orderTime;} 
};
