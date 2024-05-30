#pragma once

#include <vector>
#include <string>

#include "order.h"
#include "destination.h"

class Employee
{
public:
    const unsigned int id;
    const std::string name;
    const std::string surname;

    Employee(unsigned int id, std::string &name, std::string &surname)
        : id(id), name(name), surname(surname)
    {
    }

    std::string toString()
    {
        return std::to_string(id) + ". " + name + " " + surname;
    }
};

class Waiter : public Employee
{
    std::vector<LocalOrder *> localOrders;
    std::vector<RemoteOrder *> remoteOrders;

public:
    using Employee::Employee; // inheriting constructors from parent

    const std::vector<LocalOrder *> &getLocalOrders();
    const std::vector<RemoteOrder *> &getRemoteOrders();

    void addOrder(Order *order);
    void closeOrder(Order *order);
};