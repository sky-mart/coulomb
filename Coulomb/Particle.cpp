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
    name = "";
    m = 0;
    q = 0;
    r = Vect3();
    v = Vect3();
}

Particle::Particle(string name, double mass, double charge, Vect3 radius_vector, Vect3 velocity_vector)
{
    this->name = name;
    m = mass;
    q = charge;
    r = radius_vector;
    v = velocity_vector;
}

ostream& operator << (ostream& out, const Particle& p)
{
    out << "name: " << p.name << endl;
    out << "mass: " << p.m << endl;
    out << "charge: " << p.q << endl;
    out << "radius-vector: " << p.r << endl;
    out << "velocity vector: " << p.v << endl;
    return out;
}

Particle::Particle(string xyz_line)
{
    string ws = " \t";
    bool in_word = true;
    unsigned long word_begin = 0;
    unsigned long word_counter = 0;
    string info;
    
    for (int i = 0; i < xyz_line.length(); i++)
    {
        bool is_ws = ws.find(xyz_line[i]) != -1;
        if (in_word && is_ws)
        {
            in_word = false;
            info = xyz_line.substr(word_begin, i - word_begin);
            if (word_counter == 0)
                name = info;
            else if (word_counter == 1)
                r.x = stod(info);
            else if (word_counter == 2)
                r.y = stod(info);                
            
            word_counter++;
        }
        else if (!in_word && !is_ws)
        {
            in_word = true;
            word_begin = i;
        }
    }
    info = xyz_line.substr(word_begin, xyz_line.length() - word_begin);
    r.z = stod(info);
    
    if (name == "C")
    {
        m = 12;
        q = 0;
    }
    else if (name == "H")
    {
        m = 1;
        q = 0;
    }
    else
    {
        m = 0;
        q = 0;
    }
    
    v = Vect3();
}