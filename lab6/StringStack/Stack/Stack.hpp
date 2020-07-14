#pragma once

#include <stdio.h>
#include <string.h>
#include <stdexcept>
#include <iostream>
#include<string>

#include "StackNode.hpp"

template<class T>
class Stack;

typedef Stack<std::string> StringStack;

template<class T>
class Stack
{
public:
    Stack() = default;

    // Copying
	Stack(const Stack<T> & other)
    {
        if (other.top == nullptr)
        {
            return;
        }

        top = new StackNode<T>((T) *(other.top), nullptr);
        StackNode<T>* ptrOther = other.top->GetNext();
        StackNode<T>* ptr = top;

        try
        {
            while (ptrOther != nullptr)
            {
                auto newPtr = new StackNode<T>((T) *(ptrOther), nullptr);
                ptr->SetNext(newPtr);
                ptr = newPtr;
                ptrOther = ptrOther->GetNext();
            }
        }
        catch(...)
        {
            DeleteElements();
        }
    }

    Stack<T>& operator=(const Stack<T>& other)
    {
        if (std::addressof(other) == std::addressof(*this))
        {
            return *this;
        }

        Stack<T> newStack(other);

        std::swap(top, newStack.top);
    }

    Stack(Stack<T> && other)
    {
        top = other.top;
        other.top = nullptr;
    }

    Stack<T>& operator=(Stack<T>&& other)
    {
        if (std::addressof(other) == std::addressof(*this))
        {
            return *this;
        }

        top = other.top;
        other.top = nullptr;
    }

    ~Stack()
    {
        DeleteElements();
    }

    void Push(const T & element)
    {
        auto newTop = new StackNode<T>(element, top);
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

private:
    StackNode<T>* top = nullptr;

    void DeleteElements()
    {
        while (top != nullptr)
        {
            auto nextPtr = top->GetNext();
            delete top;
            top = nextPtr;
        }
    }
};
