//
//  Vect3.cpp
//  Coulomb
//
//  Created by Влад Агиевич on 19.10.13.
//  Copyright (c) 2013 Владислав Агиевич. All rights reserved.
//

#include "Vect3.h"

#include <cmath>

Vect3::Vect3()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Vect3::Vect3(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Vect3::Vect3(const Vect3& other)
{
    x = other.x;
    y = other.y;
    z = other.z;
}

Vect3& Vect3::operator = (const Vect3& other)
{
    if (this != &other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
    }
    return *this;
}

Vect3 Vect3::operator + (const Vect3& other) const
{
    Vect3 res;
    res.x = x + other.x;
    res.y = y + other.y;
    res.z = z + other.z;
    return res;
}

Vect3 Vect3::operator - (const Vect3& other) const
{
    Vect3 res;
    res.x = x - other.x;
    res.y = y - other.y;
    res.z = z - other.z;
    return res;
}

Vect3 Vect3::operator * (double mul) const
{
    Vect3 res;
    res.x = x * mul;
    res.y = y * mul;
    res.z = z * mul;
    return res;
}

Vect3 Vect3::operator / (double div) const
{
    Vect3 res;
    res.x = x / div;
    res.y = y / div;
    res.z = z / div;
    return res;
}

Vect3& Vect3::operator += (const Vect3& other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vect3& Vect3::operator -= (const Vect3& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

Vect3& Vect3::operator *= (double mul)
{
    x *= mul;
    y *= mul;
    z *= mul;
    return *this;
}

Vect3& Vect3::operator /= (double div)
{
    x /= div;
    y /= div;
    z /= div;
    return *this;
}

double Vect3::len() const
{
    return sqrt(x * x + y * y + z * z);
}

std::ostream& operator << (std::ostream& out, const Vect3& v)
{
    out << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return out;
}