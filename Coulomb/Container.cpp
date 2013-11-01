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
        
        side = 50;
        fillEdges();
    }
    else
        cout << "Unable to open file\n";
}

void Container::fillEdges()
{
    edges = vector<Plane>(6);
    
    Vect3 r1(-side/2, -side/2, -side/2);
    Vect3 r2(side/2, -side/2, -side/2);
    Vect3 r3(-side/2, side/2, -side/2);
    Vect3 r4(side/2, side/2, -side/2);
    Vect3 r5(-side/2, -side/2, side/2);
    Vect3 r6(side/2, -side/2, side/2);
    Vect3 r7(-side/2, side/2, side/2);
    Vect3 r8(side/2, side/2, side/2);
    
    edges[0] = Plane(r1, r2 - r1, r3 - r1);
    edges[1] = Plane(r2, r6 - r2, r4 - r2);
    edges[2] = Plane(r5, r6 - r5, r7 - r5);
    edges[3] = Plane(r1, r5 - r1, r3 - r1);
    edges[4] = Plane(r1, r2 - r1, r5 - r1);
    edges[5] = Plane(r3, r4 - r3, r7 - r3);
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

void Container::model(double time)
{
    for (double t = 0; t <= time; t += timeStep)
        oneStep();
}

void Container::oneStep()
{
    vector<Vect3> forces(N);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (i != j)
                forces[i] += particles[i].coulombForce(particles[j]);
    
    for (int i = 0; i < N; i++)
    {
        bool boundary = false;
        Vect3 newV = particles[i].getV() + forces[i] * timeStep / particles[i].getM();
        Vect3 newR = particles[i].getR() + newV * timeStep;
        
        for (int j = 0; j < edges.size(); j++)
        {
            Vect3* intersectPoint = edges[j].intersects(particles[i].getR(), newR);
            if (intersectPoint)
            {
                useBoundaryCondition(particles[i], newR, newV, edges[i], *intersectPoint);
                boundary = true;
                break;
            }
        }
        
        if (!boundary)
        {
            particles[i].move(newR, newV);
        }
            
    }
}

double Container::getTimeStep()
{
    return timeStep;
}

void Container::setTimeStep(double newStep)
{
    timeStep = newStep;
}

void Container::useBoundaryCondition(Particle& p, const Vect3& newR, const Vect3& newV,
                                     const Plane& edge, const Vect3& intersectPoint)
{
    Vect3 toReflect = intersectPoint - newR;
    Vect3 normal = edge.normal();
    Vect3 direction = toReflect.projection(normal);
    direction *= 2;
    
    Vect3 reflected = newR + direction;
    p.setR(reflected); //не все так просто, нужно еще раз проверить не пересекаем ли мы границу
}

