#include "table.h"

LocalOrder& Table::getOrder() const
{
    if (this->order == nullptr)
        throw (std::runtime_error("Cannot access order - table is free."));
    return *this->order;
}