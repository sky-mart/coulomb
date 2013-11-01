//
//  Container.h
//  Coulomb
//
//  Created by Влад Агиевич on 19.10.13.
//  Copyright (c) 2013 Владислав Агиевич. All rights reserved.
//

#ifndef __Coulomb__Container__
#define __Coulomb__Container__

#include <string>

#include <vector>
#include "Particle.h"
#include "Plane.h"

using namespace std;

class Container
{
public:
    Container(string xyz_file);
    
    static void generateUniformGrid(string xyz_file, double side, ParticleInfo part, double step);
    
    void model(double time);
    void useBoundaryCondition(Particle& p, const Vect3& newR, const Vect3& newV,
                              const Plane& edge, const Vect3& intersectPoint);
    
    double getTimeStep();
    void setTimeStep(double newStep);
    
private:
    void fillEdges();
    void oneStep();
    
    double side; //side of the cube in ångstroms
    double timeStep; //step in femtoseconds
    
    string comment; //comment in xyz file
    
    vector<Particle> particles;
    int N;
    
    vector<Plane> edges;
    
    friend ostream& operator << (ostream& out, const Container& c);
};

ostream& operator << (ostream& out, const Container& c);


#endif /* defined(__Coulomb__Container__) */
