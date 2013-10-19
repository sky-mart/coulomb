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

using namespace std;

class Particle
{
public:
    Particle(string name, double mass, double charge, Vect3 radius_vector, Vect3 velocity_vector);
    Particle(string xyz_line);
    Particle();
    
    static const double uam;
    
    Vect3 r;  //radius-vector
    Vect3 v;  //velocity vector
    double m; //mass
    double q; //charge
    string name;
};

ostream& operator << (ostream& out, const Particle& p);

#endif /* defined(__Coulomb__Particle__) */
