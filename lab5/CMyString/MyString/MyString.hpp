#pragma once
#include <string>

class MyString
{
private:
    char* buffer;
    size_t size;

public:
	MyString();

	MyString(const char * pString);

	MyString(const char * pString, size_t length);

	// Copying
	MyString(MyString const& other);
	MyString& operator=(const MyString& x);

	// Movement
	MyString(MyString && other);
	MyString& operator=(MyString&& x);

	MyString(std::string const& stlString);

	~MyString();

	size_t GetLength() const;

	const char* GetStringData() const;

	// возвращает подстроку с заданной позиции длиной не больше length символов
	MyString SubString(size_t start, size_t length) const;

	void Clear();
};
