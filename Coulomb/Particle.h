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
#include "ParticleInfo.h"

#include <iostream>

using namespace std;

class Particle
{
public:
    Particle(string name, double mass, double charge, Vect3 radius_vector, Vect3 velocity_vector);
    Particle(ParticleInfo info, Vect3 radius_vector, Vect3 velocity_vector);
    Particle(string xyz_line);
    Particle();

    Vect3 coulombForce(const Particle& other) const;
    void move(const Vect3& newR, const Vect3& newV);
    
    Vect3 getR() const;
    Vect3 getV() const;
    ParticleInfo getInfo() const;
    string getName() const;
    double getM() const;
    uint getQ() const;
    
    void setR(Vect3 r);
    void setV(Vect3 v);
    void setInfo(ParticleInfo info);
    
    static const double uam;
    
private:
    // length in ångstrems
    Vect3 r;  //radius-vector
    Vect3 v;  //velocity vector
    ParticleInfo info;
    
    friend ostream& operator << (ostream& out, const Particle& p);
};

ostream& operator << (ostream& out, const Particle& p);

#endif /* defined(__Coulomb__Particle__) */
