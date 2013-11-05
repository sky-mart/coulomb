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
            {
                forces[i] += particles[i].coulombForce(particles[j]);
                for (int k = 0; k < edges.size(); k++)
                {
                    Vect3* proj = pointProjection(particles[i].getR(), edges[k]);
                    double dist = (particles[i].getR() - (*proj)).len();
                    if (dist < 10)
                        forces[i] += reflectForce(particles[i].getR(), *proj);
                    delete proj;
                }
            }
    
    for (int i = 0; i < N; i++)
    {
        Vect3 newV = particles[i].getV() + forces[i] * timeStep / particles[i].getM();
        Vect3 newR = particles[i].getR() + newV * timeStep;
        
        /*pair<Plane, Vect3>* intersectPair = NULL;
        while ((intersectPair = intersectsEdges(particles[i], newR, newV)) != NULL)
        {
            particles[i].move(intersectPair->second, newV);
            reflect(intersectPair->first, intersectPair->second, newR, newV);
        }*/
        
        particles[i].move(newR, newV);
            
    }
}

pair<Plane, Vect3>* Container::intersectsEdges(const Particle& p, const Vect3& newR, const Vect3& newV)
{
    for (int j = 0; j < edges.size(); j++)
    {
        Vect3* intersectPoint = edges[j].intersects(p.getR(), newR);
        if (intersectPoint)
            return new pair<Plane, Vect3>(edges[j], *intersectPoint);
    }
    return NULL;
}

void Container::reflect(const Plane& plane, const Vect3& from, Vect3& to, Vect3& velocity)
{
    Vect3 segmentToReflect = from - to;
    Vect3 normal = plane.normal();
    Vect3 summand = segmentToReflect.projection(normal);
    summand *= 2;
    
    to += summand;
    
    Vect3 vDirection = to - from;
    vDirection /= vDirection.len();
    velocity = vDirection * velocity.len();
}

Vect3* Container::pointProjection(const Vect3& point, const Plane& plane)
{
    Vect3 norm = plane.normal();
    return plane.intersects(point, norm);
}

Vect3 Container::reflectForce(const Vect3& particleR, const Vect3& planeR)
{
    const double sigma = 1;
    Vect3 force = particleR - planeR;
    return force * sigma / pow(force.len(), 7);
}

double Container::getTimeStep()
{
    return timeStep;
}

void Container::setTimeStep(double newStep)
{
    timeStep = newStep;
}

