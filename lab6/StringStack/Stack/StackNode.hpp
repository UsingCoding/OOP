#pragma once

#include "Stack.hpp"

template<class T>
class StackNode
{
private:
    T data;
    StackNode* next;
public:
    StackNode(const T & data, StackNode* next): data(data), next(next) {}
    ~StackNode() {}

    StackNode<T>* GetNext()
    {
        return next;
    }

    void SetNext(StackNode<T>* ptr)
    {
        next = ptr;
    }

    operator T()
    {
        return data;
    }
};
