#include "employee.h"

Employee::Employee(unsigned int id, const std::string &name,
    const std::string &surname)
    : id(id),
      name(name),
      surname(surname)
{
}

std::string Employee::toString() const
{
    return std::to_string(this->id) + ". " + this->name + " " + this->surname;
}