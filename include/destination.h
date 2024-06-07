#pragma once

struct Destination
{
    virtual Destination& get() = 0;

    virtual ~Destination() = default;
};