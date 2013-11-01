//
//  ParticleInfo.h
//  Coulomb
//
//  Created by Влад Агиевич on 30.10.13.
//  Copyright (c) 2013 Владислав Агиевич. All rights reserved.
//

#ifndef __Coulomb__ParticleInfo__
#define __Coulomb__ParticleInfo__

#include <iostream>

using namespace std;

class ParticleInfo
{
public:
    static const string names[];
    static const double masses[];
    static const double charges[];
    static const int knownNum;
    
    ParticleInfo();
    ParticleInfo(string name);
    ParticleInfo(string name, double mass, double charge);
    
    double getM() const;
    double getQ() const;
    string getName() const;
    
    void setM(double mass);
    void setQ(double charge);
    void setName(string name);
    
private:
    double m; //mass
    double q; //charge
    string name;
    
    friend ostream& operator << (ostream& out, const ParticleInfo& p);
};

ostream& operator << (ostream& out, const ParticleInfo& p);

#endif /* defined(__Coulomb__ParticleInfo__) */
