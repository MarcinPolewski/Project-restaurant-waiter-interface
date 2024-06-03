#pragma once

#include "destination.h"
#include "address.h"

struct Remote : public Destination
{
    const std::string name;
    const std::string phoneNumber;
    const Address address;

    Remote(const std::string& nme, const std::string& pNumber, const Address& addr)
        : name(nme), phoneNumber(pNumber), address(addr) {}

    Remote& get() override {return *this;}
};
