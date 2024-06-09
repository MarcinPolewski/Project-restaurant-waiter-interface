#pragma once

#include <string>

class Employee
{
public:
    const unsigned int id;
    const std::string name;
    const std::string surname;

    Employee(unsigned int id, const std::string &name, const std::string &surname)
        : id(id), name(name), surname(surname)
    {
    }

    std::string toString()
    {
        return std::to_string(id) + ". " + name + " " + surname;
    }
};