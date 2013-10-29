//
//  Container.cpp
//  Coulomb
//
//  Created by Влад Агиевич on 19.10.13.
//  Copyright (c) 2013 Владислав Агиевич. All rights reserved.
//

#include "Container.h"

#include <fstream>
#include <cmath>

Container::Container(string xyz_file)
{
    string line;
    ifstream xyz;
    xyz.open(xyz_file, std::ifstream::in);
    
    if (xyz.good())
    {
        getline(xyz, line);
        N = stoi(line);
        particles.resize(N);
        
        getline(xyz, line);
        comment = line;
        
        int i = 0;
        while (xyz.good())
        {
            getline (xyz, line);
            if (!line.empty())
            {
                particles[i] = Particle(line);
                i++;
            }
        }
        xyz.close();
    }
    else
        cout << "Unable to open file\n";
}

ostream& operator << (ostream& out, const Container& c)
{
    for (int i = 0; i < c.particles.size(); i++)
    {
        out << "Particle #" << i + 1 << ":\n";
        out << c.particles[i] << endl;
    }
    return out;
}

void Container::generateUniformGrid(string xyz_file, double side, ParticleInfo part, double step)
{
    //Defininition of particles number works only for cases side % step == 0
    //TODO: calc other cases
    int particlesNum = pow(side / step, 3);
    string sNum = to_string(particlesNum);
    
    ofstream xyz;
    xyz.open(xyz_file, std::ofstream::out);
    if (xyz.good())
    {
        xyz << sNum << endl;
        xyz << "Uniform cube grid of " << part.getName() << endl;
        
        for (double x = -side/2 + step/2; x <= side/2 - step/2; x += step)
            for (double y = -side/2 + step/2; y <= side/2 - step/2; y += step)
                for (double z = -side/2 + step/2; z <= side/2 - step/2; z += step)
                {
                    xyz << part.getName() << ' '
                        << x << ' '
                        << y << ' '
                        << z << endl;
                }
        xyz.close();
    }
    else
        cout << "Unable to open file\n";
}

