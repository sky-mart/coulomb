//
//  main.cpp
//  Coulomb
//
//  Created by Влад Агиевич on 19.10.13.
//  Copyright (c) 2013 Владислав Агиевич. All rights reserved.
//

#include <iostream>
#include <iomanip>

#include "Particle.h"
#include "Container.h"

#include "tests.h"

using namespace std;

int main(int argc, const char * argv[])
{
    Container::generateUniformGrid("/users/vlad/uniformgrid.xyz", 50, ParticleInfo("K+"), 5);
    Container c("/users/vlad/uniformgrid.xyz");
    c.setTimeStep(1);
    cout << c;
    
    c.model(1, 1000);
    cout << c;

    
    return 0;
}

