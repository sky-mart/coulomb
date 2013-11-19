//
//  main.cpp
//  Coulomb
//
//  Created by Влад Агиевич on 19.10.13.
//  Copyright (c) 2013 Владислав Агиевич. All rights reserved.
//

#include <iostream>
#include <iomanip>

#include <ctime>

#include "Particle.h"
#include "Container.h"

#include "tests.h"

using namespace std;

void research()
{
    Container::generateRandomGrid("/users/vlad/randomgrid.xyz", 100, ParticleInfo("K+"), 100);
    Container::generateRandomVelocities("/users/vlad/velocities.xyz", 0.005, ParticleInfo("K+"), 100);
    
    Container c1("/users/vlad/randomgrid.xyz", "/users/vlad/velocities.xyz");
    Container c2("/users/vlad/randomgrid.xyz", "/users/vlad/velocities.xyz");
    
    clock_t t1, t2;
    double n2time, yavorskytime;
    
    cout << "N2 calculation:" << endl;
    t1 = clock();
    c1.model(1, 1000, Container::N2, Container::xyzFile, "/users/vlad/n2movie.xyz");
    t2 = clock();
    n2time = (double)(t2 - t1) / CLOCKS_PER_SEC;
    cout << endl;
    
    cout << "Yavorsky calculation:" << endl;
    t1 = clock();
    c2.model(1, 1000, Container::yavorsky, Container::xyzFile, "/users/vlad/yavorskymovie.xyz");
    t2 = clock();
    yavorskytime = (double)(t2 - t1) / CLOCKS_PER_SEC;
    cout << endl;
    
    cout << "Results: " << endl
    << "n2: " << n2time << endl
    << "yavorsky: " << yavorskytime << endl;
}

int main(int argc, const char * argv[])
{
    //Container::generateUniformGrid("/users/vlad/uniformgrid.xyz", 10, ParticleInfo("K+"), 5);
    Container::generateRandomGrid("/users/vlad/randomgrid.xyz", 100, ParticleInfo("K+"), 100);
    Container c("/users/vlad/randomgrid.xyz");
    //cout << c;
    
    //c.model(1, 1000, Container::yavorsky, Container::xyzFile, "/users/vlad/movie.xyz");
    //cout << c;
    
    research();

    
    return 0;
}

