//
//  main.cpp
//  Coulomb
//
//  Created by Влад Агиевич on 19.10.13.
//  Copyright (c) 2013 Владислав Агиевич. All rights reserved.
//

#include <iostream>

#include "Particle.h"

using namespace std;

int main(int argc, const char * argv[])
{

    Vect3 r(1, 1, 1);
    Vect3 v(0, 0, 0);
    
    double m = 21;
    double q = 3;
    
    Particle p(m, q, r, v);
    cout << p;
    
    return 0;
}

