#pragma once

#include "destination.h"

#include <iostream>

class LocalOrder;

class Table : public Destination
{
private:
    friend class LocalOrder;

    LocalOrder* order = nullptr;
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

    LocalOrder& getOrder() const;

    Table& get() override {return *this;}

    bool isOccupied() const {return this->order != nullptr;};
};