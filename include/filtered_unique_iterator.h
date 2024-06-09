#pragma once

#include <vector>
#include <memory>
#include <functional>

template<typename T>
class filtered_unique_iterator
{
protected:
    typedef std::vector<std::unique_ptr<T>>::iterator u_iter;
    typedef std::function<bool(const std::unique_ptr<T>&)> predicate;

    u_iter current_it;
    u_iter end_it;
    predicate pred = [](const std::unique_ptr<T>&){return true;};
public:
    filtered_unique_iterator(u_iter start_it, u_iter end_it, predicate func)
        : current_it(start_it), end_it(end_it), pred(func)
    {
        if (this->current_it != this->end_it)
            this->current_it = std::find_if(this->current_it, this->end_it, pred);
    }

    filtered_unique_iterator(u_iter start_it, u_iter end_it)
        : current_it(start_it), end_it(end_it)
    {
        if (this->current_it != this->end_it)
            this->current_it = std::find_if(this->current_it, this->end_it, pred);
    }

    filtered_unique_iterator& operator++()
    {
        if (this->current_it != this->end_it)
            this->current_it = std::find_if(++this->current_it, this->end_it, pred);
        return *this;
    }

    T& operator*()
    {
        return *((*current_it).get());
    }

    bool operator!=(const filtered_unique_iterator<T>& it2) const
    {
        return this->current_it != it2.current_it;
    }
};

template<typename T>
class const_filtered_unique_iterator
{
protected:
    typedef std::vector<std::unique_ptr<T>>::const_iterator const_u_iter;
    typedef std::function<bool(const std::unique_ptr<T>&)> predicate;

    const_u_iter current_it;
    const_u_iter end_it;
    predicate pred = [](const std::unique_ptr<T>&){return true;};
public:
    const_filtered_unique_iterator(const_u_iter start_it, const_u_iter end_it, predicate func)
        : current_it(start_it), end_it(end_it), pred(func)
    {
        if (this->current_it != this->end_it)
            this->current_it = std::find_if(this->current_it, this->end_it, pred);
    }

    const_filtered_unique_iterator(const_u_iter start_it, const_u_iter end_it)
        : current_it(start_it), end_it(end_it)
    {
        if (this->current_it != this->end_it)
            this->current_it = std::find_if(this->current_it, this->end_it, pred);
    }

    const_filtered_unique_iterator& operator++()
    {
        if (this->current_it != this->end_it)
            this->current_it = std::find_if(++this->current_it, this->end_it, pred);
        return *this;
    }

    const T& operator*() const
    {
        return *((*current_it).get());
    }

    bool operator!=(const const_filtered_unique_iterator<T>& it2) const
    {
        return this->current_it != it2.current_it;
    }
};