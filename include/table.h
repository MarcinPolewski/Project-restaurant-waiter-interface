#pragma once

#include "destination.h"

class Order;

class Table : public Destination
{
private:
    Order* order = nullptr;

    friend class Restaurant;
public:
    struct Position
    {
        const unsigned int x, y;
        int level;

        Position(unsigned int xp, unsigned int yp, int lvl)
            :   x(xp), y(yp), level(lvl) {}
    };

    const Position position;
    const unsigned int seats;

    Table(const Position& pos, unsigned int sts)
        : position(pos), seats(sts) {}

    Order& getOrder() const {return *this->order;}

    Table& get() override {return *this;}

    bool isOccupied() const {return this->order != nullptr;};
};