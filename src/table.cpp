#include "table.h"

Table::Position::Position(unsigned int xp, unsigned int yp, int lvl)
    :   x(xp), y(yp), level(lvl)
{
}

std::string Table::Position::getStr() const
{
    return "(x: " + std::to_string(this->x)
        + ", y: " + std::to_string(this->y)
        + ", lvl: " + std::to_string(this->level) + ")";
}

Table::Table(const Position& pos, unsigned int sts)
    : position(pos), seats(sts)
{
}

LocalOrder& Table::getOrder() const
{
    if (this->order == nullptr)
        throw (std::runtime_error("Cannot access order - table is free."));
    return *this->order;
}

Table& Table::get()
{
    return *this;
}

bool Table::isOccupied() const
{
    return this->order != nullptr;
}

std::string Table::getPositionStr() const
{
    return this->position.getStr();
}

std::string Table::getSeatsStr() const
{
    return std::to_string(this->seats);
}