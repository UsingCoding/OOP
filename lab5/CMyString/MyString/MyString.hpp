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

	operator char*();

	MyString operator+(const MyString & string);
	MyString operator+(const char* string);
	MyString operator+(const std::string & string);

	MyString& operator+=(const MyString & string);
	MyString& operator+=(char ch);

	bool operator==(const MyString & string) const;
	bool operator!=(const MyString & string) const;

	bool operator<(const MyString & string) const;
	bool operator>(const MyString & string) const;

	bool operator<=(const MyString & string) const;
	bool operator>=(const MyString & string) const;

	char& operator[] (const int index);
    const char& operator[] (const int index) const;

	friend std::ostream& operator<< (std::ostream &out, const MyString & string);
	friend std::istream& operator>> (std::istream &in, MyString & string);
};
