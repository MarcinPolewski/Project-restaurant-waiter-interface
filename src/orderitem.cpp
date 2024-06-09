#include "orderitem.h"

#define MAX_ORDER_ITEM_PRICE 42949600

OrderItem::OrderItem(const MenuItem& menu_item, unsigned int count,
    const std::string& com, unsigned int discnt)
    : menuItem(menu_item), quantity(count)
{
    if (quantity == 0)
        throw (std::invalid_argument("Quantity cannot be 0."));
    this->addComment(com);
    this->setDiscount(discnt);
}

void OrderItem::addComment(const std::string& new_comment)
{
    if (this->getStatus() == ItemStatus::delivered)
        throw (std::runtime_error("Cannot change status, order item has already been delivered."));
    else if (this->getStatus() == ItemStatus::canceled)
        throw (std::runtime_error("Cannot change status, order item was canceled."));

    if (new_comment.size() > 255)
        throw (std::invalid_argument("Comment cannot be longer than 255 characters."));
    this->comment = new_comment;
}

const std::string& OrderItem::getComment() const
{
    return this->comment;
}

void OrderItem::setDiscount(unsigned int new_discount)
{
    if (this->getStatus() == ItemStatus::delivered)
        throw (std::runtime_error("Cannot change status, order item has already been delivered."));
    else if (this->getStatus() == ItemStatus::canceled)
        throw (std::runtime_error("Cannot change status, order item was canceled."));

    if (new_discount > 100)
        throw (std::invalid_argument("Discount must be in range 0..100 (%)."));
    this->discount = new_discount;
}

unsigned int OrderItem::getDiscount() const
{
    return this->discount;
}

void OrderItem::changeStatus(ItemStatus new_status)
{
    if (this->itemStatus == ItemStatus::delivered)
        throw (std::runtime_error("Cannot cancel already delivered order."));
    else if (new_status < this->itemStatus)
        throw (std::runtime_error("Cannot decrease item status."));
    else
        this->itemStatus = new_status;
}

void OrderItem::setOrdered()
{
    this->changeStatus(ItemStatus::ordered);
}

void OrderItem::setDelivered()
{
    this->changeStatus(ItemStatus::delivered);
}

void OrderItem::setInPreparation()
{
    this->changeStatus(ItemStatus::inPreparation);
}

void OrderItem::setReadyToDeliver()
{
    this->changeStatus(ItemStatus::readyToDeliver);
}

void OrderItem::setCancelled()
{
    this->changeStatus(ItemStatus::canceled);
}

ItemStatus OrderItem::getStatus() const
{
    return this->itemStatus;
}

unsigned int OrderItem::getPrice() const
{
    if (this->getStatus() == ItemStatus::canceled)
        return 0;
    unsigned int full_price = quantity * this->menuItem.price;
    if (full_price > MAX_ORDER_ITEM_PRICE)
        throw(std::runtime_error("Cannot compute price - overflow"));
    unsigned int discnt = (full_price * this->discount);
    if (discnt % 100 != 0)
        discnt = discnt / 100 + 1;
    else
        discnt = discnt / 100;
    return full_price - discnt;
}

time_t OrderItem::getWaitingTime() const
{
    return time(NULL) - orderTime;
}

std::string OrderItem::getPriceStr() const
{
    unsigned int mi_price = this->getPrice();
    std::string units = std::to_string(mi_price / 100);
    std::string fraction = std::to_string(mi_price % 100);
    if (fraction.length() != 2)
        fraction = "0" + fraction;
    return units + "," + fraction;
}

std::string OrderItem::getQuantityStr() const
{
    return std::to_string(this->quantity);
}

std::string OrderItem::getStatusStr() const
{
    switch (this->itemStatus)
    {
        case ItemStatus::created:
            return "created";

        case ItemStatus::ordered:
            return "ordered";

        case ItemStatus::inPreparation:
            return "in preparation";

        case ItemStatus::readyToDeliver:
            return "ready to deliver";

        case ItemStatus::delivered:
            return "delivered";

        case ItemStatus::canceled:
            return "canceled";
    }
    return "none";
}

std::string OrderItem::getDiscountStr() const
{
    return std::to_string(this->discount) + "%";
}