#include "address.h"

Address::Address(const std::string &cty, const std::string post_code,
    const std::string strt, const std::string &num, const std::string &AI)
    : city(cty),
      postalCode(post_code),
      street(strt),
      number(num),
      additionalInfo(AI)
{
}

std::string Address::getStr() const
{
    std::string output = this->street + " " + this->number + "\n" + this->postalCode + " " + this->city;
    if (additionalInfo.empty())
        return output;
    output += "\nAI: " + this->additionalInfo;
    return output;
}