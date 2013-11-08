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
#include "dcdio.h"

using namespace std;

class Container
{
public:
    Container(string xyz_file);
    
    static void generateUniformGrid(string xyz_file, double side, ParticleInfo part, double step);
    
    void model(double timeStep, double femtoseconds);
    
    double getTimeStep();
    void setTimeStep(double newStep);
    
private:
    // returns projection of point on plane
    static Vect3* pointProjection(const Vect3& point, const Plane& plane);
    
    // additional potential for reflectional boundaru conditions
    static Vect3 reflectForce(const Vect3& particleR, const Vect3& planeR);
    
    void initializeDCD(char* dcdFileName, double dcdStep);
    void writeDCDFrame();
    void printCurrentState(ofstream& out);
    
    void fillEdges();
    void oneStep();
    
    double side; //side of the cube in ångstroms
    double timeStep; //step in femtoseconds
    int nSteps;
    
    string comment; //comment in xyz file
    
    vector<Particle> particles;
    int N;
    
    vector<Plane> edges;
    
    FILE* dcd;
    char* dcdFileName;
    double dcdStep;
    
    //unused
    pair<Plane, Vect3>* intersectsEdges(const Particle& p, const Vect3& newR, const Vect3& newV);
    static void reflect(const Plane& plane, const Vect3& from, Vect3& to, Vect3& velocity);
    
    friend ostream& operator << (ostream& out, const Container& c);
};

ostream& operator << (ostream& out, const Container& c);


#endif /* defined(__Coulomb__Container__) */
