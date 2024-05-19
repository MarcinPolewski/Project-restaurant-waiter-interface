#pragma once
#include<string>

struct Address
{
    const std::string city;
    const std::string postalCode;
    const std::string street;
    const std::string number;
    const std::string additionalInfo;

    Address(const std::string& cty, const std::string post_code,
        const std::string strt, const std::string& num, const std::string& AI = "")
        : city(cty), postalCode(post_code), street(strt), number(num), additionalInfo(AI) {}

    std::string getAddress() const
    {
        std::string output = this->street + " " + this->number + "\n" + this->postalCode + " " + this->city;
        if (additionalInfo.empty())
            return output;
        output += "\nAI: " + this->additionalInfo;
        return output;
    }
};
