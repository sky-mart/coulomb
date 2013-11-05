//
//  tests.cpp
//  Coulomb
//
//  Created by Влад Агиевич on 06.11.13.
//  Copyright (c) 2013 Владислав Агиевич. All rights reserved.
//

#include "tests.h"

#include "Vect3.h"

void testScalarProduct()
{
    Vect3 v1(1, 2, 3);
    Vect3 v2(1, 1, 1);
    
    cout << "v1: " << v1 << endl;
    cout << "v2: " << v2 << endl;
    cout << "sp = " << v1.scalarProduct(v2) << endl;
}

void testVectorProduct()
{
    Vect3 v1(1, 0, 0);
    Vect3 v2(0, 1, 0);
    
    cout << "v1: " << v1 << endl;
    cout << "v2: " << v2 << endl;
    cout << "vp = " << v1.vectorProduct(v2) << endl;
}

void testMixedProduct()
{
    Vect3 v1(1, 0, 0);
    Vect3 v2(0, 1, 0);
    Vect3 v3(1, 1, 1);
    
    cout << "v1: " << v1 << endl;
    cout << "v2: " << v2 << endl;
    cout << "v3: " << v3 << endl;
    cout << "mp = " << v3.mixedProduct(v1, v2) << endl;
    
    
}
