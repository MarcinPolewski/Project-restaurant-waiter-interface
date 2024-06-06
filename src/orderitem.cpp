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
    if (new_comment.size() > 255)
        throw (std::invalid_argument("Comment cannot be longer than 255 characters."));
    this->comment = new_comment;
}

void OrderItem::setDiscount(unsigned int new_discount)
{
    if (new_discount > 100)
        throw (std::invalid_argument("Discount must be in range 0..100 (%)."));
    this->discount = new_discount;
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
    if (this->itemStatus == ItemStatus::readyToDeliver)
        this->changeStatus(ItemStatus::delivered);
    else
        throw (std::runtime_error("Unable to set delivered, item is not ready to be delivered yet."));
}

void OrderItem::setCancelled()
{
    if (this->itemStatus < ItemStatus::inPreparation)
        this->changeStatus(ItemStatus::canceled);
    else
        throw (std::runtime_error("Unable to cancel, item is already in preparation."));
}

unsigned int OrderItem::getPrice() const
{
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
