#pragma once

class Order
{
public:
    virtual void nothing() = 0;
    virtual ~Order() = default;
};

class LocalOrder : public Order
{
    void nothing() override {}
};

class RemoteOrder : public Order
{
    void nothing() override {}
};