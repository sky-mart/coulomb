//
//  ParticleInfo.cpp
//  Coulomb
//
//  Created by Влад Агиевич on 30.10.13.
//  Copyright (c) 2013 Владислав Агиевич. All rights reserved.
//

#include "ParticleInfo.h"

const int ParticleInfo::knownNum = 4;
const string ParticleInfo::names[] = {"C", "H", "K+", "Cl-"};
const double ParticleInfo::masses[] = {12, 1, 39.0983, 35.4257};
const double ParticleInfo::charges[] = {0, 0, 1, -1};

const double ParticleInfo::amu = 1.660538783e-27;   //kg
const double ParticleInfo::e = 1.602176565e-19;     //coulomb

ParticleInfo::ParticleInfo()
{
    this->m = 0;
    this->q = 0;
    this->name = "";
}

ParticleInfo::ParticleInfo(string name, double m, double q)
{
    this->m = m;
    this->q = q;
    this->name = name;
}

ParticleInfo::ParticleInfo(string name)
{
    this->name = name;
    bool known = false;
    for (int i = 0; i < knownNum; i++)
        if (name == names[i])
        {
            m = masses[i];
            q = charges[i];
            known = true;
        }
    if (!known)
    {
        m = 0;
        q = 0;
    }
}

double ParticleInfo::getM() const
{
    return m;
}

double ParticleInfo::getQ() const
{
    return q;
}

string ParticleInfo::getName() const
{
    return name;
}

void ParticleInfo::setM(double m)
{
    this->m = m;
}

void ParticleInfo::setQ(uint q)
{
    this->q = q;
}

void ParticleInfo::setName(string name)
{
    this->name = name;
}

ostream& operator << (ostream& out, const ParticleInfo& p)
{
    out << "name: " << p.name << endl
        << "mass: " << p.m << endl
        << "charge: " << p.q << endl;
    return out;
}
