#include "./MyString.hpp"
#include <stdio.h>
#include <string.h>
#include <stdexcept>


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
    buffer = new char[size + 1];
    memcpy(buffer, other.buffer, size + 1);
	other.buffer = nullptr; // Уточнить поведение

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

    for (size_t i = 0; i < length; i++)
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
