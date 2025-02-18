#include "ImaginaryPoint.h"

// Constructor
ImaginaryPoint::ImaginaryPoint(int real, int imaginary)
{
    real_part = real;
    imaginary_part = imaginary;
}

// Destructor
ImaginaryPoint::~ImaginaryPoint()
{
    // Not needed for this case
}

// Calculate magnitude squared
int ImaginaryPoint::get_magnitude_squared() const
{
    return (real_part * real_part) + (imaginary_part * imaginary_part);
}

// Getter for real part
int ImaginaryPoint::get_real_part() const
{
    return real_part;
}

// Getter for imaginary part
int ImaginaryPoint::get_imaginary_part() const
{
    return imaginary_part;
}

// Overload addition operator
ImaginaryPoint ImaginaryPoint::operator+(const ImaginaryPoint& other) const
{
    int real_addition = real_part + other.real_part;
    int imaginary_addition = imaginary_part + other.imaginary_part;
    return ImaginaryPoint(real_addition, imaginary_addition);
}

// Overload subtraction operator
ImaginaryPoint ImaginaryPoint::operator-(const ImaginaryPoint& other) const
{
    int real_subtraction = real_part - other.real_part;
    int imaginary_subtraction = imaginary_part - other.imaginary_part;
    return ImaginaryPoint(real_subtraction, imaginary_subtraction);
}

// Overload multiplication operator
ImaginaryPoint ImaginaryPoint::operator*(const ImaginaryPoint& other) const
{
    int real_multiplication = (real_part * other.real_part) + (imaginary_part * other.imaginary_part * -1);
    int imaginary_multiplication = (real_part * other.imaginary_part) + (imaginary_part * other.real_part);
    return ImaginaryPoint(real_multiplication, imaginary_multiplication);
}

// Overload less than operator
bool ImaginaryPoint::operator<(const ImaginaryPoint& other) const
{
    return (get_magnitude_squared() < other.get_magnitude_squared());
}
