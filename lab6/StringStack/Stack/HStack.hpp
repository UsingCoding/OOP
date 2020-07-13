#pragma once

#include <stdio.h>
#include <string.h>
#include <stdexcept>
#include <iostream>

template<class T>
class HStack
{
private:
    class StackNode
    {
    private:
        T data;
        StackNode* next;
    public:
        StackNode(const T & data, StackNode* next): data(data), next(next) {}
        ~StackNode() {}

        StackNode* GetNext()
        {
            return next;
        }

        void SetNext(StackNode* ptr)
        {
            next = ptr;
        }

        operator T()
        {
            return data;
        }
    };

    StackNode* top = nullptr;
public:
    HStack() = default;

    // Copying
	HStack(const HStack<T> & other)
    {
        if (other.top == nullptr)
        {
            return;
        }

        top = new StackNode((T) *(other.top), nullptr);
        StackNode* ptrOther = other.top;
        StackNode* ptr = top;

        try
        {
            while (ptrOther != nullptr)
            {
                auto newPtr = new StackNode((T) *(ptrOther), nullptr);
                ptr->SetNext(newPtr);
                ptr = newPtr;
                ptrOther = ptrOther->GetNext();
            }
        }
        catch(const std::exception& e)
        {
            ~HStack();
        }


    }

    HStack<T>& operator=(const HStack<T>& other)
    {
        if (std::addressof(other) == std::addressof(*this))
        {
            return *this;
        }

        HStack<T> newStack(other);

        std::swap(top, newStack.top);
    }

    HStack(HStack<T> && other)
    {
        top = other.top;
        other.top = nullptr;
    }

    HStack<T>& operator=(HStack<T>&& other)
    {
        if (std::addressof(other) == std::addressof(*this))
        {
            return *this;
        }

        top = other.top;
        other.top = nullptr;
    }

    ~HStack()
    {
        while (top != nullptr)
        {
            auto nextPtr = top->GetNext();
            delete top;
            top = nextPtr;
        }

    }

    void Push(const T & element)
    {
        auto newTop = new StackNode(element, top);
        top = newTop;
    }

    T Pop()
    {
        if (top == nullptr)
        {
            throw std::logic_error("Pop empty stack");
        }

        T data = *top;
        auto newTop = top->GetNext();
        delete top;
        top = newTop;

        return data;
    }
};
