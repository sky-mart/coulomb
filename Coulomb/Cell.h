//
//  Cell.h
//  Coulomb
//
//  Created by Влад Агиевич on 08.11.13.
//  Copyright (c) 2013 Владислав Агиевич. All rights reserved.
//

#ifndef __Coulomb__Cell__
#define __Coulomb__Cell__

#include <iostream>
#include <vector>
#include <list>
#include "Particle.h"

class Cell
{
    // radius-vector of cube's center
    Vect3 center;
    
    // length of cube's side
    double side;
    
    int N;
    
    double avgQ;
    Vect3 avgR;
    
    Vect3 D;
    Vect3 s;
    
    vector<Vect3> signs;
    
    vector<Cell*> subcells;
    
    bool root;
    
    bool leaf;
    list<Particle*>* particleList;
    
public:
    Cell(const Vect3& center, const double side);
    
    ~Cell();
    
    static string statisticsFile;
    
    static double G(const double R, const Vect3& s);
    
    static const double criticalSize;
    
    void setRoot(bool root);
    bool isRoot();
    
    bool isLeaf();
    
    bool operator == (const Cell& other);
    
    friend ostream& operator << (ostream& out, const Cell& c);
    
    // coulomb force from the whole cell on particle p
    Vect3 coulombForce(const Particle& p);
    
    // add a particle to this cell
    void add(Particle* p);
    
    // remove a particle from this cell
    void remove(Particle* p);
    
    // method generates subcells if their size is bigger then critical
    void generateSubcells();
    
    void hierarchy(Particle* p, vector<Cell*>& hierarchy);
    
    void interactingCells(const vector<Cell*>& hierarchy, vector<Cell*>& interacting);
    
    void printHierarchy();
    
    list<Particle*>* getParticles();
    
    list<Particle*>* allParticles();
    
    void addStatistics(const Particle& p, const Vect3& honestForce, const Vect3& yavorskyForce);
};

#endif /* defined(__Coulomb__Cell__) */
