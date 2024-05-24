#include "orderitem.h"

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

void OrderItem::addComment(std::string&& new_comment)
{
    if (new_comment.size() > 255)
        throw (std::invalid_argument("Comment cannot be longer than 255 characters."));
    this->comment = std::move(new_comment);
}

void OrderItem::setDiscount(unsigned int new_discount)
{
    if (new_discount > 100)
        throw (std::invalid_argument("Discount must be in range 0..100 (%)."));
    this->discount = new_discount;
}

void OrderItem::setDelivered()
{
    if (this->itemStatus == ItemStatus::readyToDeliver)
        this->itemStatus = ItemStatus::delivered;
    else
        throw (std::runtime_error("Unable to set delivered - item is not ready to delivered yet."));
}

void OrderItem::setCancelled()
{
    if (this->itemStatus == ItemStatus::ordered)
        this->itemStatus = ItemStatus::canceled;
    else
        throw (std::runtime_error("Unable to cancel, item is already in preparation."));
}
