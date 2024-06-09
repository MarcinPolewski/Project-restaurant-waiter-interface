#pragma once

#include <string>

struct Address
{
    const std::string city;
    const std::string postalCode;
    const std::string street;
    const std::string number;
    const std::string additionalInfo;

    Address(const std::string &cty, const std::string post_code,
            const std::string strt, const std::string &num, const std::string &AI = "");

    std::string getStr() const;
};