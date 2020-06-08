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
        buffer = new T[size + 1];
        buffer[size] = '\0';
    }

	// Copying
	MyArray(MyArray<T> const& other)
    {
        size = other.size;
        buffer = new T[size + 1];
        memcpy(buffer, other.buffer, size + 1);
    }

	MyArray<T>& operator=(const MyArray<T>& other)
    {
        if (std::addressof(other) == std::addressof(*this))
        {
            return *this;
        }

        size = other.size;

        delete[] buffer;

        buffer = new T[size + 1];
        memcpy(buffer, other.buffer, size + 1);

        return *this;
    }

	// Movement
	MyArray(MyArray<T> && other)
    {
        size = other.size;
        buffer = other.buffer;
        other.buffer = nullptr;
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
        T* tempBuffer = new T[newSize];

        memcpy(tempBuffer, buffer, newSize < size ? newSize : size);

        delete[] buffer;

        size_t diff;

        if ((diff = (newSize - size)) > 0)
        {
            for (size_t i = size; i < newSize; i++)
            {
                tempBuffer[i] = T();
            }
        }

        size = newSize;
        buffer = tempBuffer;
    }

	void Clear()
    {
        delete[] buffer;
        size = 0;
        buffer = new T[size + 1];
        buffer[size] = '\0';
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
        return buffer + size;
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

	// operator char*();


	T& operator[] (const int index)
    {
        if (index >= size)
        {
            throw std::out_of_range("");
        }

        return buffer[index];
    }

    const char& operator[] (const int index) const
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
