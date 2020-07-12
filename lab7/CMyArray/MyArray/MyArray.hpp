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
    T* m_begin;
    T* m_end;
    T* m_capacityEnd;

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

    static void CopyElements(const T * srcBegin, T * srcEnd, T * const dstBegin, T * & dstEnd)
	{
		for (dstEnd = dstBegin; srcBegin != srcEnd; ++srcBegin, ++dstEnd)
		{
			new (dstEnd)T(*srcBegin);
		}
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
	MyArray(): m_begin(nullptr), m_end(nullptr), m_capacityEnd(nullptr) {}

	// Copying
	MyArray(MyArray<T> const& other)
    {
        auto size = other.GetSize();
		if (size != 0)
		{
			m_begin = Alloc(size);
			try
			{
				CopyElements(other.m_begin, other.m_end, m_begin, m_end);
				m_capacityEnd = m_end;
			}
			catch (...)
			{
				DeleteElements(m_begin, m_end);
				throw;
			}
		}
    }

	MyArray<T>& operator=(const MyArray<T>& other)
    {
        if (std::addressof(other) == std::addressof(*this))
        {
            return *this;
        }

        MyArray newArr(other);
		std::swap(m_begin, newArr.m_begin);
		std::swap(m_end, newArr.m_end);
		std::swap(m_capacityEnd, newArr.m_capacityEnd);

        return *this;
    }

	// Movement
	MyArray(MyArray&& other):
    m_begin(other.m_begin), m_end(other.m_end), m_capacityEnd(other.m_capacityEnd)
	{
		other.m_begin = nullptr;
		other.m_end = nullptr;
		other.m_capacityEnd = nullptr;
	}

	MyArray<T>& operator=(MyArray<T>&& other)
    {
        if (std::addressof(other) == std::addressof(*this))
        {
            return *this;
        }

	    DeleteElements(m_begin, m_end);

		m_begin = other.m_begin;
		m_end = other.m_end;
		m_capacityEnd = other.m_capacityEnd;

		other.m_begin = nullptr;
		other.m_end = nullptr;
		other.m_capacityEnd = nullptr;
	    return *this;
    }

	~MyArray()
    {
        DeleteElements(m_begin, m_end);
    }

	void Clear()
    {
        DeleteElements(m_begin, m_end);

        m_begin = nullptr;
        m_end = nullptr;
        m_capacityEnd = nullptr;
    }

    void Push(const T & element)
    {
        if (m_capacityEnd == m_end)
        {
            auto newCapacity = std::max(size_t(1), GetCapacity() * 2);
            Reserve(newCapacity);
        }

        new (m_end) T(element);
        ++m_end;
    }

    size_t GetCapacity() const
    {
        return m_capacityEnd - m_end;
    }

    size_t GetSize() const
    {
        return m_end - m_begin;
    }

    void Reserve(size_t newCapacity)
    {
        if (GetCapacity() >= newCapacity)
        {
            return;
        }

        auto newBegin = Alloc(newCapacity);
        T* newEnd = newBegin;

        if (GetSize() != 0)
        {
            try
			{
				CopyElements(m_begin, m_end, newBegin, newEnd);
			}
			catch (...)
			{
				DeleteElements(newBegin, newEnd);
				throw;
			}
        }

        DeleteElements(m_begin, m_end);

        m_begin = newBegin;
		m_end = newEnd;
		m_capacityEnd = m_begin + newCapacity;
    }

    void Resize(size_t size)
    {
        if (size != GetSize())
        {
            MyArray newArr;
			newArr.Reserve(size);

			size_t minSize = std::min(GetSize(), size);
			for (size_t i = 0; i < minSize; ++i)
			{
				newArr.Push(*(m_begin + i));
			}
			for (size_t i = GetSize(); i < size; ++i)
			{
				newArr.Push(T());
			}

			*this = std::move(newArr);
        }
    }

	template<bool reverse>
	class iterator;

    typedef iterator<false> Iterator;
	typedef const iterator<false> ConstIterator;

    typedef iterator<true> IteratorReverse;
	typedef const iterator<true> ConstIteratorReverse;

	Iterator begin()
    {
        return m_begin;
    }

	Iterator end()
    {
        return m_end;
    }

	ConstIterator begin() const
    {
        return m_begin;
    }

	ConstIterator end() const
    {
        return m_end;
    }

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

        return m_begin[index];
    }

    const T& operator[] (const int index) const
    {
        if (index >= GetSize())
        {
            throw std::out_of_range("");
        }

        return m_begin[index];
    }

    template<bool reverse>
	class iterator
	{
	private:
        T* beginPtr;
        T* endPtr;
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
