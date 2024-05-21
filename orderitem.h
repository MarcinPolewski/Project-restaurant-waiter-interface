#pragma once
#include "menuItem.h"
#include<time.h>

class OrderItem
{
private:
    unsigned int discount = 0;
public:
    const MenuItem& menuItem;
    std::string comment;
    const time_t orderTime;
};
