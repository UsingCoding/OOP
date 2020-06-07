#include "./Complex.hpp"
#include "../../../Utils/StringUtils.hpp"
#include <cmath>
#include <stdexcept>
#include <float.h>
#include <math.h>

#include <iostream>

Complex::Complex(double real, double image): real(real), image(image) {}

double Complex::Re() const
{
    return real;
}

double Complex::Im() const
{
    return image;
}

double Complex::GetMagnitude() const
{
    return sqrt(pow(real, 2) + pow(image, 2));
}

double Complex::GetArgument() const
{
    if (real == 0)
    {
        throw std::domain_error("You can`t divide by zero");
    }

    return atan(image/real) * 180.0 / M_PI;
}

Complex Complex::operator+(const Complex & other)
{
    return Complex(real + other.real, image + other.image);
}

Complex Complex::operator-(const Complex & other)
{
    return Complex(real - other.real, image - other.image);
}

Complex Complex::operator*(const Complex & other)
{
    return Complex(real * other.real - image * other.image, real * other.image + image * other.real);
}

Complex Complex::operator/(const Complex & other)
{
    return Complex(
        (real * other.real - image * other.image) / (pow(real, 2) + pow(image, 2)),
        (real * other.image + image * other.real) / (pow(real, 2) + pow(image, 2))
    );
}

Complex Complex::operator+()
{
    return Complex(real, image);
}
Complex Complex::operator-()
{
    return Complex(-real, -image);
}

Complex Complex::operator+=(const Complex & other)
{
    real += other.real;
    image += other.image;
}

Complex Complex::operator-=(const Complex & other)
{
    real -= other.real;
    image -= other.image;
}

Complex Complex::operator*=(const Complex & other)
{
    real = real * other.real - image * other.image;
    image = real * other.image + image * other.real;
}

Complex Complex::operator/=(const Complex & other)
{
    real = (real * other.real - image * other.image) / (pow(real, 2) + pow(image, 2));
    image = (real * other.image + image * other.real) / (pow(real, 2) + pow(image, 2));
}

bool Complex::operator==(const Complex & other) const
{
    bool realsAreEqual = fabs(real - other.real) < DBL_EPSILON;
    bool imagesAreEqual = fabs(image - other.image) < DBL_EPSILON;

    return realsAreEqual && imagesAreEqual;
}

bool Complex::operator!=(const Complex & other) const
{
    return !(*this == other);
}

std::ostream& operator<< (std::ostream &out, const Complex & complex)
{
    StringUtils::StringConcatenator result;

    if (complex.real != 0)
    {
        if (complex.real < 0)
        {
            result << '-';
        }

        result << complex.real;
    }

    if (complex.image != 0)
    {
        result << (complex.image > 0 ? '+' : '-') << complex.image;
    }

    return out << (std::string) result << Complex::I;
}

std::istream& operator>> (std::istream &in, Complex & complex)
{
    in >> complex.real;
    in >> complex.image;

    return in;
}
