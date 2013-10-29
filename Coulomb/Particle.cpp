//
//  Particle.cpp
//  Coulomb
//
//  Created by Влад Агиевич on 19.10.13.
//  Copyright (c) 2013 Владислав Агиевич. All rights reserved.
//

#include "Particle.h"

const double Particle::uam = 1.66e-27;

Particle::Particle()
{
    info = ParticleInfo();
    r = Vect3();
    v = Vect3();
}

Particle::Particle(string name, double mass, double charge, Vect3 radius_vector, Vect3 velocity_vector)
{
    info = ParticleInfo(name, mass, charge);
    r = radius_vector;
    v = velocity_vector;
}

Vect3 Particle::getR()
{
    return r;
}

Vect3 Particle::getV()
{
    return v;
}

ParticleInfo Particle::getInfo()
{
    return info;
}

string Particle::getName()
{
    return info.getName();
}

double Particle::getM()
{
    return info.getM();
}

double Particle::getQ()
{
    return info.getQ();
}

void Particle::setR(Vect3 r)
{
    this->r = r;
}

void Particle::setV(Vect3 v)
{
    this->v = v;
}

void Particle::setInfo(ParticleInfo info)
{
    this->info = info;
}

ostream& operator << (ostream& out, const Particle& p)
{
    out << p.info
        << "radius-vector: " << p.r << endl
        << "velocity vector: " << p.v << endl;
    return out;
}

Particle::Particle(string xyz_line)
{
    string ws = " \t";
    bool in_word = true;
    unsigned long word_begin = 0;
    unsigned long word_counter = 0;
    string word;
    
    for (int i = 0; i < xyz_line.length(); i++)
    {
        bool is_ws = ws.find(xyz_line[i]) != -1;
        if (in_word && is_ws)
        {
            in_word = false;
            word = xyz_line.substr(word_begin, i - word_begin);
            if (word_counter == 0)
                info = ParticleInfo(word);
            else if (word_counter == 1)
                r.x = stod(word);
            else if (word_counter == 2)
                r.y = stod(word);
            
            word_counter++;
        }
        else if (!in_word && !is_ws)
        {
            in_word = true;
            word_begin = i;
        }
    }
    word = xyz_line.substr(word_begin, xyz_line.length() - word_begin);
    r.z = stod(word);
    
    v = Vect3();
}