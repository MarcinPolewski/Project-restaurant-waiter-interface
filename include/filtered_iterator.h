#pragma once

#include <vector>
#include <functional>

template<typename T>
class filtered_iterator
{
protected:
    typedef std::vector<T*>::iterator iter;
    typedef std::function<bool(T*)> predicate;

    iter current_it;
    iter end_it;
    predicate pred = [](const T*){return true;};
public:
    filtered_iterator(iter start_it, iter end_it, predicate func)
        : current_it(start_it), end_it(end_it), pred(func)
    {
        if (this->current_it != this->end_it)
            this->current_it = std::find_if(this->current_it, this->end_it, pred);
    }

    filtered_iterator(iter start_it, iter end_it)
        : current_it(start_it), end_it(end_it)
    {
        if (this->current_it != this->end_it)
            this->current_it = std::find_if(this->current_it, this->end_it, pred);
    }

    filtered_iterator& operator++()
    {
        if (this->current_it != this->end_it)
            this->current_it = std::find_if(++this->current_it, this->end_it, pred);
        return *this;
    }

    T& operator*()
    {
        return **current_it;
    }

    bool operator!=(const filtered_iterator<T>& it2) const
    {
        return this->current_it != it2.current_it;
    }
};