//
//  ParticleInfo.h
//  Coulomb
//
//  Created by Влад Агиевич on 30.10.13.
//  Copyright (c) 2013 Владислав Агиевич. All rights reserved.
//

#ifndef __Coulomb__ParticleInfo__
#define __Coulomb__ParticleInfo__

typedef unsigned int uint;

#include <iostream>

using namespace std;

class ParticleInfo
{
public:
    static const string names[];
    static const double masses[];
    static const double charges[];
    static const int knownNum;
    
    static const double amu;    //atomic mass unit in kg
    static const double e;      //electron's charge in coulombs
    
    ParticleInfo();
    ParticleInfo(string name);
    ParticleInfo(string name, double mass, double charge);
    
    double getM() const;
    double getQ() const;
    string getName() const;
    
    void setM(double mass);
    void setQ(uint charge);
    void setName(string name);
    
    bool operator == (const ParticleInfo& other);
    
private:
    double m;   //mass in aems
    uint q;     //charge in electron charges
    string name;
    
    friend ostream& operator << (ostream& out, const ParticleInfo& p);
};

ostream& operator << (ostream& out, const ParticleInfo& p);

#endif /* defined(__Coulomb__ParticleInfo__) */
