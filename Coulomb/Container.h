//
//  Container.h
//  Coulomb
//
//  Created by Влад Агиевич on 19.10.13.
//  Copyright (c) 2013 Владислав Агиевич. All rights reserved.
//

#ifndef __Coulomb__Container__
#define __Coulomb__Container__

#include <fstream>
#include <string>
#include <vector>
#include "Particle.h"
#include "Plane.h"
#include "Cell.h"
#include "dcdio.h"

using namespace std;

class Container
{
    
public:
    // Enumeration of output modes.
    // At the moment only writing to .xyz files works
    // and oportunity to write to .dcd files also exists but doesn't work
    enum OutputMode {xyzFile, dcdFile, noOutput};
    
    
    // Enumeration of coulomb force calculation methods
    // At the moment only the simplest N^2 method works
    enum CoulombCalc {N2, yavorsky, statistics};
    
    
    // Constructor from file .xyz @xyzFile
    // File has to be a bit special:
    // the 2nd should contain length of cube's side
    Container(string xyzFile);
    
    Container(string coordinateFile, string velocityFile);
        
    
    // This method generates uniform grid which has
    // particles in every node. All particles are situated
    // in cube with side's length equal to @side
    // Uniform grid is being written to file @xyzFile
    static void generateUniformGrid(string xyzFile, double side, ParticleInfo part, double step);
    
    
    // Generates random cube grid with @nParticles particles
    static void generateRandomGrid(string xyzFile, double side, ParticleInfo part, int nParticles);
    
    static void generateRandomVelocities(string xyzFile, double maxVelocity, ParticleInfo part, int nParticles);
    
    
    // Basic method to model participles movement
    // during @femtoseconds femtoseconds with the
    // time step equal to @timeStep
    void model(double timeStep, double time, CoulombCalc calc, OutputMode outputMode, const string& outputFile);
    
    
    // Getter/setter of timeStep parameter
    double getTimeStep();
    void setTimeStep(double newStep);
    
    
    // Returns projection of point on plane
    static Vect3* pointProjection(const Vect3& point, const Plane& plane);
    
    // Potential for reflectional boundary conditions
    static Vect3 reflectForce(const Vect3& particleR, const Vect3& planeR);
    
    
    // Unused
    pair<Plane, Vect3>* intersectsEdges(const Particle& p, const Vect3& newR, const Vect3& newV);
    static void reflect(const Plane& plane, const Vect3& from, Vect3& to, Vect3& velocity);
    
private:
    
    // Basic method modelling one step
    void oneStep();
    void statisticsStep();
    
    // Methods specific for yavorsky calculactions
    void generateCells();
    void defineParticlesSets();
    void recalcCells(int i);
    
    // Method defining if I should print smth on this step
    bool shouldOutput(double timeFromStart);
    
    // DCD methods
    void initializeDCD(char* dcdFileName, double dcdStep);
    void writeDCDFrame();
    
    // write current system state to .xyz file @movie
    void printCurrentState();
    
    void printHierarchy(int i);
    void printInteracting(int i);
    
    // Initialization of side surfaces
    void fillEdges();
    
    string comment; //comment in xyz file
    
    // Geometry
    
    // Side of the cube in ångstroms
    double side;
    
    // 6 side surfaces of cube
    vector<Plane> edges;
    
    // Distance where boundary potential starts working
    static const double boundaryDistance;
    
    // Interpretation of container as the biggest cell
    Cell* cell;
    
    
    // Time parameters
    
    // Step in femtoseconds
    double timeStep;
    
    // set of particles inside the cube
    int N;
    vector<Particle> particles;
    
    // Hierarchy of particle which has information
    // what cells particle belongs to
    vector<vector<Cell*>> hierarchy;
    
    // Set of cells and particles particle #i interacts with
    vector<vector<Cell*>> interactingCells;
    
    CoulombCalc calc;
    
    OutputMode outputMode;
    
    // DCD variables
    /*DCD dcd;
    char* dcdFileName;
    int dcdStep;*/
    
    // .xyz file
    ofstream movie;
    
    friend ostream& operator << (ostream& out, const Container& c);
};

ostream& operator << (ostream& out, const Container& c);


#endif /* defined(__Coulomb__Container__) */
