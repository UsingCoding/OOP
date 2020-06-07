#pragma once

#include <iosfwd>

class Complex
{
public:
    Complex(double real = 0, double image = 0);

	// возвращает действительную часть комплексного числа
	double Re()const;

	// возвращает мнимую часть комплексного числа
	double Im()const;

	// возвращает модуль комплексного числа
	double GetMagnitude()const;

	// возвращает аргумент комплексного числа
	double GetArgument()const;

	Complex operator+(const Complex & other);

	Complex operator-(const Complex & other);

	Complex operator*(const Complex & other);

	Complex operator/(const Complex & other);

	Complex operator+();
	Complex operator-();

	Complex operator+=(const Complex & other);

	Complex operator-=(const Complex & other);

	Complex operator*=(const Complex & other);

	Complex operator/=(const Complex & other);

	bool operator==(const Complex & other) const;

	bool operator!=(const Complex & other) const;

	friend std::ostream& operator<< (std::ostream &out, const Complex & complex);
	friend std::istream& operator>> (std::istream &in, Complex & complex);

private:
    double real;
    double image;

	static const char I = 'i';
};
