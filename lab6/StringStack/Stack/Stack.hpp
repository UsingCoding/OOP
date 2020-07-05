#pragma once

#include <stdio.h>
#include <string.h>
#include <stdexcept>
#include <iostream>

template<class T>
class Stack;

// typedef Stack<std::string> StringStack;
typedef Stack<int> StringStack;

template<class T>
class Stack
{
private:
    T* buffer;
    size_t size;
public:
    Stack(): buffer(nullptr), size(0) {}

    // Copying
	Stack(Stack<T> const& other)
    {
        buffer = new T[other.size];
        size = other.size;
        memcpy(buffer, other.buffer, sizeof(T) * size);
    }

	Stack<T>& operator=(const Stack<T>& other)
    {
        if (std::addressof(other) == std::addressof(*this))
        {
            return *this;
        }

        size = other.size;

        delete[] buffer;

        buffer = new T[size];
        memcpy(buffer, other.buffer, sizeof(T) * size);

        return *this;
    }

	// Movement
	Stack(Stack<T> && other)
    {
        size = other.size;
        buffer = other.buffer;
        other.buffer = nullptr;
        other.size = 0;
    }

	Stack<T>& operator=(Stack<T>&& other)
    {
        if (std::addressof(other) == std::addressof(*this))
        {
            return *this;
        }

	    delete[] buffer;

        size = other.size;
        buffer = other.buffer;
	    other.buffer = nullptr;
        other.size = 0;

	    return *this;
    }

    void Push(T element)
    {
        T* tempBuffer = new T[size + 1]();

        if (buffer != nullptr)
        {
            memcpy(tempBuffer, buffer, size);
        }

        delete[] buffer;

        size = size + 1;
        buffer = tempBuffer;

        buffer[size - 1] = element;
    }

    T Pop()
    {
        if (size == 0)
        {
            throw std::logic_error("Trying to pop empty stack");
        }

        T* tempBuffer = new T[size - 1]();

        if (buffer != nullptr)
        {
            memcpy(tempBuffer, buffer + 1, size - 1);
        }

        T result = *buffer;
        delete[] buffer;

        size = size - 1;
        buffer = tempBuffer;

        return result;
    }

    size_t GetSize()
    {
        return size;
    }

    ~Stack()
    {
        delete[] buffer;
    }
};
