#pragma once

#include "HStack.hpp"

template<class T>
class StackNode
{
private:
    template<class T> friend class HStack<T>;
    T data;
    StackNode<T>* next;
public:
    StackNode(const T & data, StackNode<T>* next): data(data), next(next) {}
    ~StackNode() {}

    StackNode<T>* GetNext()
    {
        return next;
    }

    operator T()
    {
        return data;
    }
};
