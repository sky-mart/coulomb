//
//  Particle.h
//  Coulomb
//
//  Created by Влад Агиевич on 19.10.13.
//  Copyright (c) 2013 Владислав Агиевич. All rights reserved.
//

#ifndef __Coulomb__Particle__
#define __Coulomb__Particle__

#include "Vect3.h"

#include <iostream>

class Particle
{
public:
    Particle(double mass, double charge, Vect3 radius_vector, Vect3 velocity_vector);
    
    Vect3 r;  //radius-vector
    Vect3 v;  //velocity vector
    double m; //mass
    double q; //charge
};

std::ostream& operator << (std::ostream& out, const Particle& p);

#endif /* defined(__Coulomb__Particle__) */
