#pragma once
#include <stdio.h>
#include <string.h>
#include <stdexcept>
#include <algorithm>
#include <new>


#include <iostream>

template<class T>
class MyArray
{
private:
    T* begin;
    T* end;
    T* capacityEnd;

    static T* Alloc(size_t n)
    {
        size_t memSize = n * sizeof(T);
		T *ptr = static_cast<T*>(malloc(memSize));
		if (ptr == nullptr)
		{
			throw std::bad_alloc();
		}
		return ptr;
    }

    static void DeleteElements(T* begin, T* end)
    {
        DestroyElements(begin, end);
        Free(begin);
    }

    static void DestroyElements(T* src, T* dest)
	{
		while (dest != src)
		{
			--dest;
			dest->~T();
		}
	}

    static void Free(T* ptr)
    {
        free(ptr);
    }

public:
	MyArray(): begin(nullptr), end(nullptr), capacityEnd(nullptr) {}

	// Copying
	// MyArray(MyArray<T> const& other)
    // {
    //     begin = new T[other.size];
    //     size = other.size;
    //     memcpy(begin, other.begin, sizeof(T) * size);
    // }

	// MyArray<T>& operator=(const MyArray<T>& other)
    // {
    //     if (std::addressof(other) == std::addressof(*this))
    //     {
    //         return *this;
    //     }

    //     size = other.size;

    //     delete[] begin;

    //     begin = new T[size];
    //     memcpy(begin, other.begin, sizeof(T) * size);

    //     return *this;
    // }

	// // Movement
	// MyArray(MyArray<T> && other)
    // {
    //     size = other.size;
    //     begin = other.begin;
    //     other.begin = nullptr;
    //     other.size = 0;
    // }

	// MyArray<T>& operator=(MyArray<T>&& other)
    // {
    //     if (std::addressof(other) == std::addressof(*this))
    //     {
    //         return *this;
    //     }

	//     delete[] begin;

    //     size = other.size;
    //     begin = other.begin;
	//     other.begin = nullptr;
    //     other.size = 0;

	//     return *this;
    // }

	~MyArray()
    {
        DeleteElements(begin, end);
        // delete[] begin;
    }

	void Clear()
    {
        DeleteElements(begin, end);

        begin = nullptr;
        end = nullptr;
        capacityEnd = nullptr;
    }

    void Push(const T & element)
    {
        if (capacityEnd == end)
        {
            auto newCapacity = std::max(size_t(1), GetCapacity() * 2);
            Reserve(newCapacity);
        }

        new (end) T(element);
        ++end;
    }

    size_t GetCapacity() const
    {
        return capacityEnd - end;
    }

    size_t GetSize() const
    {
        return end - begin;
    }

    void Reserve(size_t newCapacity)
    {
        if (GetCapacity() >= newCapacity)
        {
            return;
        }

        auto newBegin = Alloc(newCapacity);

        if (GetSize() != 0)
        {
            memcpy(newBegin, begin, GetSize());
        }

        DeleteElements(begin, end);

        auto size = (GetSize() == 0 ? newCapacity : GetSize());
        begin = newBegin;
        end = begin + size;
        capacityEnd = begin + newCapacity;
    }

    void Resize(size_t size)
    {
        if (size != GetSize())
        {
            size_t minSize = std::min(GetSize(), size);
            auto tempBuffer = Alloc(minSize);

            memcpy(tempBuffer, begin, minSize);

            for (size_t i = GetSize(); i < size; i++)
            {
                tempBuffer[i] = new T();
            }

            DeleteElements(begin, end);

            begin = tempBuffer;
            end = begin + size;
            capacityEnd = end > capacityEnd ? end : capacityEnd;
        }
    }

	template<bool reverse>
	class iterator;

    typedef iterator<false> Iterator;
	typedef const iterator<false> ConstIterator;

    typedef iterator<true> IteratorReverse;
	typedef const iterator<true> ConstIteratorReverse;

	// Iterator begin()
    // {
    //     return begin;
    // }

	// Iterator end()
    // {
    //     return end;
    // }

	// ConstIterator begin() const
    // {
    //     return begin;
    // }

	// ConstIterator end() const
    // {
    //     return end;
    // }

    // IteratorReverse rbegin()
    // {
    //     return end - 1;
    // }

	// IteratorReverse rend()
    // {
    //     return begin;
    // }

	// ConstIteratorReverse rbegin() const
    // {
    //     return end - 1;
    // }

	// ConstIteratorReverse rend() const
    // {
    //     return begin;
    // }

	T& operator[] (const int index)
    {
        if (index >= GetSize())
        {
            throw std::out_of_range("");
        }

        return begin[index];
    }

    const T& operator[] (const int index) const
    {
        if (index >= GetSize())
        {
            throw std::out_of_range("");
        }

        return begin[index];
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
