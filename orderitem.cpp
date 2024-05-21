#include "orderitem.h"

OrderItem::OrderItem(const MenuItem& menu_item, unsigned int count,
    unsigned int discnt, const std::string& com)
    : menuItem(menu_item), quantity(count)
{
    this->add_comment(com);
    this->add_discount(discnt);
}

void OrderItem::add_comment(const std::string& new_comment)
{
    if (new_comment.size() > 255)
        throw (std::invalid_argument("Comment cannot be longer than 255 characters."));
    this->comment = new_comment;
}

const std::string& OrderItem::get_comment() const {return this->comment;}

void OrderItem::add_discount(unsigned int new_discount)
{
    if (new_discount > 100)
        throw (std::invalid_argument("Discount must be in range 0..100 (%)."));
    this->discount = new_discount;
}

unsigned int OrderItem::get_discount() const {return this->discount;}