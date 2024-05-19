#pragma once
#include "address.h"

struct Destination
{
    virtual Destination& get() = 0;

    virtual ~Destination() = default;
};

struct Table : public Destination
{
    struct Position
    {
        const unsigned int x, y;
        int level;

        Position(unsigned int xp, unsigned int yp, int lvl)
            :   x(xp), y(yp), level(lvl) {}
    };

    const Position position;
    const unsigned int seats;
    bool occupied = false;

    Table(const Position& pos, unsigned int sts)
        : position(pos), seats(sts) {}

    Destination& get() override {return *this;}

    bool isOccupied() const {return occupied;}
};

struct Remote : public Destination
{
    const Address address;

    Remote(const Address& addr)
        : address(addr) {}

    Destination& get() override {return *this;}
};
