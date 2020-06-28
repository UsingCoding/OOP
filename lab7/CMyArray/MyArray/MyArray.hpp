#pragma once
#include <stdio.h>
#include <string.h>
#include <stdexcept>

#include <iostream>

template<class T>
class MyArray
{
private:
    T* buffer;
    size_t size;

public:
	MyArray()
    {
        size = 0;
        buffer = nullptr;
    }

	// Copying
	MyArray(MyArray<T> const& other)
    {
        buffer = new T[other.size];
        size = other.size;
        memcpy(buffer, other.buffer, sizeof(T) * size);
    }

	MyArray<T>& operator=(const MyArray<T>& other)
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
	MyArray(MyArray<T> && other)
    {
        size = other.size;
        buffer = other.buffer;
        other.buffer = nullptr;
        other.size = 0;
    }

	MyArray<T>& operator=(MyArray<T>&& other)
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

	~MyArray()
    {
        delete[] buffer;
    }

	size_t GetLength() const
    {
        return size;
    }

	void Resize(size_t newSize)
    {
        T* tempBuffer = new T[newSize]();

        if (buffer != nullptr)
        {
            memcpy(tempBuffer, buffer, newSize < size ? sizeof(T) * newSize : sizeof(T) * size);
        }

        delete[] buffer;

        size = newSize;
        buffer = tempBuffer;
    }

	void Clear()
    {
        delete[] buffer;
        size = 0;
        buffer = nullptr;
    }

    void Push(T element)
    {
        Resize(size + 1);
        buffer[size - 1] = element;
    }

	template<bool reverse>
	class iterator;

    typedef iterator<false> Iterator;
	typedef const iterator<false> ConstIterator;

    typedef iterator<true> IteratorReverse;
	typedef const iterator<true> ConstIteratorReverse;

	Iterator begin()
    {
        return buffer;
    }

	Iterator end()
    {
        return buffer + size;
    }

	ConstIterator begin() const
    {
        return buffer;
    }

	ConstIterator end() const
    {
        return buffer + size;
    }

    IteratorReverse rbegin()
    {
        return buffer + size - 1;
    }

	IteratorReverse rend()
    {
        return buffer;
    }

	ConstIteratorReverse rbegin() const
    {
        return buffer + size - 1;
    }

	ConstIteratorReverse rend() const
    {
        return buffer;
    }

	T& operator[] (const int index)
    {
        if (index >= size)
        {
            throw std::out_of_range("");
        }

        return buffer[index];
    }

    const T& operator[] (const int index) const
    {
        if (index >= size)
        {
            throw std::out_of_range("");
        }

        return buffer[index];
    }

    template<bool reverse>
	class iterator
	{
	private:
		mutable T* curr;
	public:
		iterator(T* curr): curr(curr){}

		iterator<reverse> operator++(int) const
        {
            if (reverse)
            {
                return curr--;
            }
            else
            {
                return curr++;
            }
        }

		iterator<reverse> operator--(int) const
        {
            if (reverse)
            {
                return curr++;
            }
            else
            {
                return curr--;
            }
        }

		iterator<reverse> operator++() const
        {
            if (reverse)
            {
                return --curr;
            }
            else
            {
                return ++curr;
            }
        }

		iterator<reverse> operator--() const
        {
            if (reverse)
            {
                return ++curr;
            }
            else
            {
                return --curr;
            }
        }

		bool operator!=(const iterator<reverse> & it) const
        {
            return curr != it.curr;
        }

		bool operator==(const iterator<reverse> & it) const
        {
            return curr == it.curr;
        }

		T& operator*()
        {
            return *curr;
        }
		const T& operator*() const
        {
            return *curr;
        }
	};
};
