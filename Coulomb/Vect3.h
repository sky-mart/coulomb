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

using namespace std;

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
    
    bool operator == (const Vect3 other);
    
    double len() const;
    
    double scalarProduct(const Vect3& other) const;
    Vect3 vectorProduct(const Vect3& other) const;
    double mixedProduct(const Vect3& other1, const Vect3& other2) const;
    
    Vect3 projection(const Vect3& other) const;
    double projectionCoeff(const Vect3& other) const;
    
    double x;
    double y;
    double z;
};

std::ostream& operator << (std::ostream& stream, const Vect3& v);

#endif /* defined(__Coulomb__Vect3__) */
