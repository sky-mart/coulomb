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
#include <fstream>

using namespace std;

void research(const string& gridFile, int fromParticles, int toParticles, int particleStep,
              int nTimeSteps, const string& outputFile)
{
    ofstream out;
    out.open(outputFile, ofstream::out);
    if (out.good())
    {
        for (int i = fromParticles; i < fromParticles; i += particleStep)
        {
            out << i << ' ';
            Container::generateRandomGrid(gridFile, 100, ParticleInfo("K+"), i);
            //Container::generateRandomVelocities("/users/vlad/velocities.xyz", 0.005, ParticleInfo("K+"), 100);
            
            Container c1(gridFile);//, "/users/vlad/velocities.xyz");
            Container c2(gridFile);//, "/users/vlad/velocities.xyz");
            
            clock_t t1, t2;
            double n2time, yavorskytime;
            
            //cout << "N2 calculation:" << endl;
            t1 = clock();
            c1.model(1, nTimeSteps, Container::N2, Container::noOutput, "");
            t2 = clock();
            n2time = (double)(t2 - t1) / CLOCKS_PER_SEC;
            //cout << endl;
            
            //cout << "Yavorsky calculation:" << endl;
            t1 = clock();
            c2.model(1, nTimeSteps, Container::yavorsky, Container::noOutput, "");
            t2 = clock();
            yavorskytime = (double)(t2 - t1) / CLOCKS_PER_SEC;
            //cout << endl;
            
            out << n2time << ' ' << yavorskytime << endl;
        }
        out.close();
    }
}

void statistics(const string& grid, const string& output)
{
    Container::generateRandomGrid(grid, 100, ParticleInfo("K+"), 100);
    Container c(grid);
    
    c.model(1, 1000, Container::statistics, Container::noOutput, "");
}

int main(int argc, const char * argv[])
{
    if (argc == 1)
    {
        cout << "Usage: " << endl
        << argv[0] << " -stat gridFile statFile" << endl
        << argv[0] << " -research gridFile fromParticles toParticles particleStep nTimeSteps outputFile" << endl;
    }
    else if (argc == 4 && (strcmp(argv[1], "-stat") == 0))
    {
        statistics(argv[2], argv[3]);
    }
    else if (argc == 8 && (strcmp(argv[1], "-research") == 0))
    {
        int fromParticles = atoi(argv[3]);
        int toParticles = atoi(argv[4]);
        int particleStep = atoi(argv[5]);
        int nTimeSteps = atoi(argv[6]);
        research(argv[2], fromParticles, toParticles, particleStep, nTimeSteps, argv[7]);
    }
    
    return 0;
}

