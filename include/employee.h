#pragma once

#include <string>

class Employee
{
public:
    const unsigned int id;
    const std::string name;
    const std::string surname;

    Employee(unsigned int id, const std::string &name,
        const std::string &surname);

    std::string toString() const;
};