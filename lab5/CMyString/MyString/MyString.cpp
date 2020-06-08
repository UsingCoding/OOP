#include "./MyString.hpp"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdexcept>
#include <cstring>
#include <cstdio>

MyString::MyString()
{
    size = 0;
    buffer = new char[size + 1];
    buffer[size] = '\0';
}

MyString::MyString(const char * pString)
{
    size = strlen(pString);
    buffer = new char[size + 1];
    memcpy(buffer, pString, size);
    buffer[size] = '\0';
}

MyString::MyString(const char * pString, size_t length): size(length)
{
    buffer = new char[size + 1];
    memcpy(buffer, pString, size);
    buffer[size] = '\0';
}

// Copying
MyString::MyString(MyString const& other)
{
    size = other.size;
    buffer = new char[size + 1];
    memcpy(buffer, other.buffer, size + 1);
}

MyString& MyString::operator=(const MyString& other)
{
    if (std::addressof(other) == std::addressof(*this))
    {
        return *this;
    }

    size = other.size;

    delete[] buffer;

    buffer = new char[size + 1];
    memcpy(buffer, other.buffer, size + 1);

    return *this;
}

// Movement
MyString::MyString(MyString && other)
{
    size = other.size;
    buffer = other.buffer;
    other.buffer = nullptr;
}

MyString& MyString::operator=(MyString&& other)
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

MyString::MyString(std::string const& stlString)
{
    size = stlString.size();
    // Проверить содержит ли std::string нуль-терминальный символ
    buffer = new char[size + 1];
    memcpy(buffer, stlString.c_str(), size);
    buffer[size] = '\0';
}


MyString::~MyString()
{
    delete[] buffer;
}

size_t MyString::GetLength() const
{
    return size;
}

const char* MyString::GetStringData() const
{
    return buffer;
}

// возвращает подстроку с заданной позиции длиной не больше length символов
MyString MyString::SubString(size_t start, size_t length) const
{
    if (length > size)
    {
        throw std::invalid_argument("Trying to access data outside string");
    }

    char result[length];

    for (size_t i = start; i < length; i++)
    {
        result[i] = buffer[i];
    }

    return MyString(result);
}

void MyString::Clear()
{
    delete[] buffer;
    size = 0;
    buffer = new char[size + 1];
    buffer[size] = '\0';
}

MyString::Iterator MyString::begin()
{
    return buffer;
}

MyString::Iterator MyString::end()
{
    return buffer + size;
}

MyString::ConstIterator MyString::begin() const
{
    return buffer;
}

MyString::ConstIterator MyString::end() const
{
    return buffer + size;
}

MyString::operator char*()
{
    return buffer;
}

// Operators

MyString MyString::operator+(const MyString & string)
{
    return MyString(std::strcat(buffer, string.buffer));
}

MyString MyString::operator+(const char* string)
{
    return  *this + MyString(string);
}

MyString MyString::operator+(const std::string & string)
{
    return *this + MyString(string);
}

MyString& MyString::operator+=(const MyString & string)
{
    buffer = (*this + string);
    return *this;
}

MyString& MyString::operator+=(char ch)
{
    char* tempBuffer = new char[size + 2];
    memcpy(tempBuffer, buffer, size);

    delete[] buffer;
    ++size;

    tempBuffer[size - 1] = ch;
    tempBuffer[size] = '\0';

    buffer = tempBuffer;
    tempBuffer = nullptr;
}

bool MyString::operator==(const MyString & string) const
{
    if (size != string.size)
    {
        return false;
    }

    for (size_t i = 0; i < size; i++)
    {
        if (buffer[i] != string.buffer[i])
        {
            return false;
        }
    }

    return true;
}

bool MyString::operator!=(const MyString & string) const
{
    return (*this == string);
}

bool MyString::operator<(const MyString & string) const
{
    MyString substr;

    try
    {
        substr = string.SubString(0, size);
    }
    catch(const std::invalid_argument& e)
    {
        return false;
    }

    return *this == substr;
}

bool MyString::operator>(const MyString & string) const
{
    return string < *this;
}

bool MyString::operator<=(const MyString & string) const
{
    return *this < string || *this == string;
}

bool MyString::operator>=(const MyString & string) const
{
    return *this > string || *this == string;
}

char& MyString::operator[] (const int index)
{
    if (index >= size)
    {
        throw std::out_of_range("");
    }

    return buffer[index];
}

const char& MyString::operator[] (const int index) const
{
    if (index >= size)
    {
        throw std::out_of_range("");
    }

    return buffer[index];
}

std::ostream& operator<< (std::ostream &out, const MyString & string)
{
    return out << string.buffer;
}

std::istream& operator>> (std::istream &in, MyString & string)
{
    char ch;
    while ((ch = in.get()) != '\n' && ch != ' ')
    {
        string += ch;
    }

    return in;
}


MyString::Iterator& MyString::Iterator::operator+=(int n)
{
    curr += n;
    return *this;
}

MyString::Iterator& MyString::Iterator::operator-=(int n)
{
    *curr -= n;
    return *this;
}

int MyString::Iterator::operator-(const Iterator it) const
{
    return curr - it.curr;
}

MyString::Iterator MyString::Iterator::operator++(int) const
{
    return curr++;
}

MyString::Iterator MyString::Iterator::operator--(int) const
{
    return curr--;
}

MyString::Iterator MyString::Iterator::operator++() const
{
    return ++curr;
}

MyString::Iterator MyString::Iterator::operator--() const
{
    return --curr;
}

bool MyString::Iterator::operator!=(const Iterator & it) const
{
    return curr != it.curr;
}

bool MyString::Iterator::operator==(const Iterator & it) const
{
    return curr == it.curr;
}

char& MyString::Iterator::operator*()
{
    return *curr;
}

const char& MyString::Iterator::operator*() const
{
    return *curr;
}
