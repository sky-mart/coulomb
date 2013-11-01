//
//  main.cpp
//  Coulomb
//
//  Created by Влад Агиевич on 19.10.13.
//  Copyright (c) 2013 Владислав Агиевич. All rights reserved.
//

#include <iostream>

#include "Particle.h"
#include "Container.h"

using namespace std;

int main(int argc, const char * argv[])
{
    //Container::generateUniformGrid("/users/vlad/uniformgrid.xyz", 50, ParticleInfo("C"), 3);
    //Container c("/users/vlad/uniformgrid.xyz");
    //cout << c;
    
    Particle p1("p1", 1, 2, Vect3(0, 1, 0), Vect3(0, 0, 0));
    Particle p2("p2", 1, -4, Vect3(1, 1, 0), Vect3(0, 0, 0));
    
    cout << p1.coulombForce(p2) << endl;
    return 0;
}

