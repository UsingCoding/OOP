#pragma once

#include <stdio.h>
#include <string.h>
#include <stdexcept>
#include <algorithm>
#include <new>

template <typename T>
class MyArray
{

public:
	MyArray() = default;

    // Copying
	MyArray(const MyArray& other)
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
				DeleteItems(m_begin, m_end);
				throw;
			}
		}
	}

    MyArray& operator=(const MyArray & other)
	{
		if (std::addressof(other) == std::addressof(*this))
		{
		    return *this;
		}

        MyArray tempArr(other);
		std::swap(m_begin, tempArr.m_begin);
		std::swap(m_end, tempArr.m_end);
		std::swap(m_capacityEnd, tempArr.m_capacityEnd);
	}

    // Movement
	MyArray(MyArray && other):
    m_begin(other.m_begin), m_end(other.m_end), m_capacityEnd(other.m_capacityEnd)
	{
		other.m_begin = nullptr;
		other.m_end = nullptr;
		other.m_capacityEnd = nullptr;
	}

    MyArray& operator=(MyArray && other)
	{
		if (std::addressof(other) == std::addressof(*this))
		{
    		return *this;
		}

        DeleteItems(m_begin, m_end);

		m_begin = other.m_begin;
		m_end = other.m_end;
		m_capacityEnd = other.m_capacityEnd;

		other.m_begin = nullptr;
		other.m_end = nullptr;
		other.m_capacityEnd = nullptr;
	}

	~MyArray()
	{
		DeleteItems(m_begin, m_end);
	}

	void Push(const T & value)
	{
		if (m_end == m_capacityEnd)
		{
			size_t newCapacity = std::max(size_t(1), GetCapacity() * 2);
			Reserve(newCapacity);
		}
		new (m_end) T(value);
		++m_end;
	}

	size_t GetSize() const
	{
		return m_end - m_begin;
	}

	size_t GetCapacity() const
	{
		return m_capacityEnd - m_begin;
	}

	const T& operator[](const size_t index) const
	{
		if (index >= GetSize())
		{
			throw std::out_of_range("Out of range");
		}

		return *(m_begin + index);
	}

	T& operator[](const size_t index)
	{
		if (index >= GetSize())
		{
			throw std::out_of_range("Out of range");
		}

		return *(m_begin + index);
	}

	void Reserve(size_t newCapacity)
	{
		if (GetCapacity() >= newCapacity)
		{
			return;
		}

		auto newBegin = Alloc(newCapacity);
		T *newEnd = newBegin;

		if (GetSize() != 0)
		{
			try
			{
				CopyElements(m_begin, m_end, newBegin, newEnd);
			}
			catch (...)
			{
				DeleteItems(newBegin, newEnd);
				throw;
			}
		}
		DeleteItems(m_begin, m_end);

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

	void Clear()
	{
		DeleteItems(m_begin, m_end);

		m_begin = nullptr;
		m_end = nullptr;
		m_capacityEnd = nullptr;
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

    IteratorReverse rbegin()
    {
        return m_end - 1;
    }

	IteratorReverse rend()
    {
        return m_begin - 1;
    }

	ConstIteratorReverse rbegin() const
    {
        return m_end -1;
    }

	ConstIteratorReverse rend() const
    {
        return m_begin - 1;
    }

    template<bool reverse>
	class iterator
	{
	private:
		mutable T* m_curr;
	public:
		iterator(T* curr): m_curr(curr){}

		iterator<reverse> operator++(int) const
        {
            if (reverse)
            {
                return m_curr--;
            }
            else
            {
                return m_curr++;
            }
        }

		iterator<reverse> operator--(int) const
        {
            if (reverse)
            {
                return m_curr++;
            }
            else
            {
                return m_curr--;
            }
        }

		iterator<reverse> operator++() const
        {
            if (reverse)
            {
                return --m_curr;
            }
            else
            {
                return ++m_curr;
            }
        }

		iterator<reverse> operator--() const
        {
            if (reverse)
            {
                return ++m_curr;
            }
            else
            {
                return --m_curr;
            }
        }

		bool operator!=(const iterator<reverse> & it) const
        {
            return m_curr != it.m_curr;
        }

		bool operator==(const iterator<reverse> & it) const
        {
            return m_curr == it.m_curr;
        }

		T& operator*()
        {
            return *m_curr;
        }
		const T& operator*() const
        {
            return *m_curr;
        }
	};

private:
    T *m_begin = nullptr;
	T *m_end = nullptr;
	T *m_capacityEnd = nullptr;

	static void DeleteItems(T *begin, T *end)
	{
		DestroyElements(begin, end);
		Free(begin);
	}

	static void CopyElements(T* srcBegin, T* srcEnd, T * dstBegin, T * & dstEnd)
	{
		for (dstEnd = dstBegin; srcBegin != srcEnd; ++srcBegin, ++dstEnd)
		{
			new (dstEnd)T(*srcBegin);
		}
	}

	static void DestroyElements(T *stc, T *dest)
	{
		while (dest != stc)
		{
			--dest;
			dest->~T();
		}
	}

	static T* Alloc(size_t n)
	{
		size_t memSize = n * sizeof(T);
		T *p = static_cast<T*>(malloc(memSize));
		if (!p)
		{
			throw std::bad_alloc();
		}
		return p;
	}

	static void Free(T *p)
	{
		free(p);
	}
};
