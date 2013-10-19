//
//  Container.cpp
//  Coulomb
//
//  Created by Влад Агиевич on 19.10.13.
//  Copyright (c) 2013 Владислав Агиевич. All rights reserved.
//

#include "Container.h"

#include <fstream>

Container::Container(string xyz_file)
{
    ifstream xyz(xyz_file);
    string line;
    
    if (xyz.is_open())
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
            particles[i] = Particle(line);
            i++;
        }
        xyz.close();
    }
    else
        cout << "Unable to open file";
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

