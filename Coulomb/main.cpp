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

    Container c("/Users/Vlad/Dev/Univer/Coulomb/methane.xyz");
    cout << c;
    return 0;
}

