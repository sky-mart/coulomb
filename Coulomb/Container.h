//
//  Container.h
//  Coulomb
//
//  Created by Влад Агиевич on 19.10.13.
//  Copyright (c) 2013 Владислав Агиевич. All rights reserved.
//

#ifndef __Coulomb__Container__
#define __Coulomb__Container__

#include <string>

#include <vector>
#include "Particle.h"

using namespace std;

class Container
{
public:
    Container(string xyz_file);
    
private:
    double len; //side of the cube
    
    string comment;
    int N;
    vector<Particle> particles;
    
    friend ostream& operator << (ostream& out, const Container& c);
};

ostream& operator << (ostream& out, const Container& c);


#endif /* defined(__Coulomb__Container__) */
