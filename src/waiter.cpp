#include "waiter.h"

std::vector<LocalOrder *> Waiter::getLocalOrders()
{
    std::vector<LocalOrder *> temp;
    for (auto it : localOrders)
        temp.push_back(&it);

    return temp;
}

std::vector<RemoteOrder *> Waiter::getRemoteOrders()
{
    std::vector<RemoteOrder *> temp;
    for (auto it : remoteOrders)
        temp.push_back(&it);

    return temp;
}

bool Waiter::hasOrders()
{
    return !(localOrders.empty() && remoteOrders.empty());
}