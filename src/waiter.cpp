#include "waiter.h"

const std::vector<LocalOrder *> &Waiter::getLocalOrders()
{
    return localOrders;
}

const std::vector<RemoteOrder *> &Waiter::getRemoteOrders()
{
    return remoteOrders;
}

void Waiter::addOrder(Order *order)
{
    LocalOrder *localOrder = dynamic_cast<LocalOrder *>(order);
    if (localOrder) // true if order is a local order
    {
        localOrders.push_back(localOrder);
    }
    else
    {
        remoteOrders.push_back(dynamic_cast<RemoteOrder *>(order));
    }
}

void Waiter::closeOrder(Order *order)
{
    LocalOrder *localOrder = dynamic_cast<LocalOrder *>(order);
    if (localOrder) // true if order is a local order
    {
        std::vector<LocalOrder *>::const_iterator it = std::find(localOrders.cbegin(), localOrders.cend(), localOrder);
        if (it == localOrders.end())
            throw std::runtime_error("Local orders do not have such an error");
        localOrders.erase(it);
    }
    else
    {
        RemoteOrder *remoteOrder = dynamic_cast<RemoteOrder *>(order);
        std::vector<RemoteOrder *>::const_iterator it = std::find(remoteOrders.cbegin(), remoteOrders.cend(), remoteOrder);
        if (it == remoteOrders.end())
            throw std::runtime_error("Remote orders do not have such an error");
        remoteOrders.erase(it);
    }
}

bool Waiter::hasOrders()
{
    return !(localOrders.empty() && remoteOrders.empty());
}