//
//  Square.h
//  Coulomb
//
//  Created by Влад Агиевич on 31.10.13.
//  Copyright (c) 2013 Владислав Агиевич. All rights reserved.
//

#ifndef __Coulomb__Square__
#define __Coulomb__Square__

#include <iostream>
#include "Vect3.h"

class Plane
{
public:
    Plane();
    Plane(Vect3 r0, Vect3 a, Vect3 b);
    
    Vect3* intersects(const Vect3& r1, const Vect3& r2) const;
    bool hasPoint(const Vect3& r) const;
    bool squareHasPoint(const Vect3& r) const;
    bool intersectsStraight(const Vect3& l) const;
    Vect3* getIntersectPoint(const Vect3& r1, const Vect3& r2) const;
    Vect3 normal() const;
    
private:
    Vect3 r0;
    Vect3 a;
    Vect3 b;
};

#endif /* defined(__Coulomb__Square__) */
