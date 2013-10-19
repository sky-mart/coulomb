//
//  Vect3.h
//  Coulomb
//
//  Created by Влад Агиевич on 19.10.13.
//  Copyright (c) 2013 Владислав Агиевич. All rights reserved.
//

#ifndef __Coulomb__Vect3__
#define __Coulomb__Vect3__

#include <iostream>

class Vect3
{
public:
    Vect3();
    Vect3(double x, double y, double z);
    Vect3(const Vect3& other);
    Vect3& operator = (const Vect3& other);
    
    Vect3 operator + (const Vect3& other) const;
    Vect3 operator - (const Vect3& other) const;
    Vect3 operator * (double mul) const;
    Vect3 operator / (double div) const;
    
    Vect3& operator += (const Vect3& other);
    Vect3& operator -= (const Vect3& other);
    Vect3& operator *= (double mul);
    Vect3& operator /= (double div);
    
    double len() const;
    
    double x;
    double y;
    double z;
};

std::ostream& operator << (std::ostream& stream, const Vect3& v);

#endif /* defined(__Coulomb__Vect3__) */
