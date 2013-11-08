//
//  Square.cpp
//  Coulomb
//
//  Created by Влад Агиевич on 31.10.13.
//  Copyright (c) 2013 Владислав Агиевич. All rights reserved.
//

#include "Plane.h"

Plane::Plane()
{
    this->r0 = Vect3();
    this->a = Vect3();
    this->b = Vect3();
}

Plane::Plane(Vect3 r0, Vect3 a, Vect3 b)
{
    this->r0 = r0;
    this->a = a;
    this->b = b;
}

Vect3* Plane::segmentIntersectsSquare(const Vect3& from, const Vect3& to) const
{
    if (straightIntersectsPlane(to - from)) //straight doesn't intersect the plane
    {
        if (planeHasPoint(from)) //whole straight lies in the plane
            return new Vect3(from);
        else //straight and plane go in parallel
            return NULL;
    }
    else //straight intersects the plane, how about segment and square?
    {
        Vect3* intersectPoint = getIntersectPoint(from, to);
        if (squareHasPoint(*intersectPoint))
            return intersectPoint;
        else
            return NULL;
    }
}

bool Plane::planeHasPoint(const Vect3& r) const
{
    return (r - r0).mixedProduct(a, b) == 0;
}

bool Plane::squareHasPoint(const Vect3& r) const
{
    double rProjACoeff = r.projectionCoeff(a);
    double rProjBCoeff = r.projectionCoeff(b);
    return (rProjACoeff >= 0 && rProjACoeff <= 1) &&
           (rProjBCoeff >= 0 && rProjBCoeff <= 1);
}

bool Plane::straightIntersectsPlane(const Vect3& l) const
{
    return l.mixedProduct(a, b) == 0;
}

Vect3* Plane::getIntersectPoint(const Vect3& r1, const Vect3& r2) const
{
    /*
     прямая:
     r = r1 + t(r2-r1)
     плоскость:
     r = r0 + u*a + v*b
     6 неизвестных, 6 уравнений
     или по-другому
     r1 + t(r2-r1) = r0 + u*a + v*b
     3 уравнения, 3 неизвестных
     
     x1 + t(x2-x1) = x0 + u*A + v*D
     y1 + t(y2-y1) = y0 + u*B + v*E
     z1 + t(z2-z1) = z0 + u*C + v*F
     
     перепишем в виде:
     (x2-x1)*t - A*u - D*v = x0 - x1
     (y2-y1)*t - B*u - E*v = y0 - y1
     (z2-z1)*t - C*u - F*v = z0 - z1
     
     в матричном виде:
     (x2-x1  -A  -D) (t) = (x0-x1)
     (y2-y1  -B  -E) (u) = (y0-y1)
     (z2-z1  -C  -F) (v) = (z0-z1)
     
     дальше можно решить методом крамера
     */
    double a11 = r2.x - r1.x;
    double a12 = -a.x;
    double a13 = -b.x;
    double a21 = r2.y - r1.y;
    double a22 = -a.y;
    double a23 = -b.y;
    double a31 = r2.z - r1.z;
    double a32 = -a.z;
    double a33 = -b.z;
    
    double d1 = r0.x - r1.x;
    double d2 = r0.y - r1.y;
    double d3 = r0.z - r1.z;
    
    double detA = a11 * (a22 * a33 - a23 * a32) -
    a12 * (a21 * a33 - a23 * a31) +
    a13 * (a21 * a32 - a22 * a31);
    
    double det1 = d1 * (a22 * a33 - a23 * a32) -
    a12 * (d2 * a33 - a23 * d3) +
    a13 * (d2 * a32 - a22 * d3);
    
    /*
    double det2 = a11 * (d2 * a33 - a23 * d3) -
    d1 * (a21 * a33 - a23 * a31) +
    a13 * (a21 * d3 - d2 * a31);
    
    double det3 = a11 * (a22 * d3 - d2 * a32) -
    a12 * (a21 * d3 - d2 * a31) +
    d1 * (a21 * a32 - a22 * a31);
    */
    double t = det1 / detA;
    //double u = det2 / detA;
    //double v = det3 / detA;
    
    return new Vect3(r1 + (r2 - r1) * t);
}

Vect3 Plane::normal() const
{
    return a.vectorProduct(b);
}
