//
//  Particle.cpp
//  Coulomb
//
//  Created by Влад Агиевич on 19.10.13.
//  Copyright (c) 2013 Владислав Агиевич. All rights reserved.
//

#include "Particle.h"

Particle::Particle(double mass, double charge, Vect3 radius_vector, Vect3 velocity_vector)
{
    m = mass;
    q = charge;
    r = radius_vector;
    v = velocity_vector;
}

std::ostream& operator << (std::ostream& out, const Particle& p)
{
    out << "mass: " << p.m << std::endl;
    out << "charge: " << p.q << std::endl;
    out << "radius-vector: " << p.r << std::endl;
    out << "velocity vector: " << p.v << std::endl;
    return out;
}