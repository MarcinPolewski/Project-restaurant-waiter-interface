#pragma once

#include <vector>
#include <string>

#include "order.h"
#include "destination.h"

class Employee
{
public:
    const std::string name;
    const std::string surname;
    const unsigned int id;

    Employee(std::string &name, std::string &surname, unsigned int id)
        : name(name), surname(surname), id(id)
    {
    }

    std::string toString()
    {
        return std::to_string(id) + ". " + name + " " + surname;
    }
};

class Waiter : public Employee
{
    std::vector<LocalOrder> localOrders;
    std::vector<RemoteOrder> remoteOrders;

public:
    using Employee::Employee; // inheriting constructors from parent

    std::vector<LocalOrder *> getLocalOrders();
    std::vector<RemoteOrder *> getRemoteOrders();

    void newOrder(Table *table);
    void newOrder(Remote *remote);

    void closeOrder(Order *order);

    bool hasOrders();
};