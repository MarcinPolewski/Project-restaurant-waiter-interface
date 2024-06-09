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

        Position(unsigned int xp, unsigned int yp, int lvl);

        std::string getStr() const;
    };

    const Position position;
    const unsigned int seats;

    Table(const Position& pos, unsigned int sts);

    LocalOrder& getOrder() const;

    Table& get() override;

    bool isOccupied() const;

    std::string getPositionStr() const;
    std::string getSeatsStr() const;
};