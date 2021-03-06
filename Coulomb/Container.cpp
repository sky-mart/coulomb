//
//  Container.cpp
//  Coulomb
//
//  Created by Влад Агиевич on 19.10.13.
//  Copyright (c) 2013 Владислав Агиевич. All rights reserved.
//

#include "Container.h"

#include <fstream>
#include <iomanip>
#include <cmath>

const double Container::boundaryDistance = 10;

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
        unsigned long sideIndex = comment.find("side=") + 5;
        side = stoi(comment.substr(sideIndex, comment.length() - sideIndex));
        
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

        fillEdges();
    }
    else
        cout << "Unable to open file\n";
}

Container::Container(string coordinateFile, string velocityFile)
{
    ifstream coordinate;
    ifstream velocity;
    
    string line;
    
    coordinate.open(coordinateFile, std::ifstream::in);
    
    if (coordinate.good())
    {
        getline(coordinate, line);
        N = stoi(line);
        particles.resize(N);
        
        getline(coordinate, line);
        comment = line;
        unsigned long sideIndex = comment.find("side=") + 5;
        side = stoi(comment.substr(sideIndex, comment.length() - sideIndex));
        
        int i = 0;
        while (coordinate.good())
        {
            getline (coordinate, line);
            if (!line.empty())
            {
                particles[i] = Particle(line);
                i++;
            }
        }
        coordinate.close();
        
        fillEdges();
    }
    else
    {
        cout << "Unable to open file\n";
        exit(0);
    }
    
    velocity.open(coordinateFile, std::ifstream::in);
    
    if (velocity.good())
    {
        getline(velocity, line);
        getline(velocity, line);
        
        int i = 0;
        while (velocity.good())
        {
            getline (velocity, line);
            if (!line.empty())
            {
                particles[i].setV(line);
                i++;
            }
        }
        velocity.close();
        
        fillEdges();
    }
    else
    {
        cout << "Unable to open file\n";
        exit(0);
    }

    
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
    xyz.open(xyz_file, ofstream::out);
    if (xyz.good())
    {
        xyz << sNum << endl;
        xyz << "Uniform cube grid of " << part.getName() << ", side=" << side << endl;
        
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

void Container::generateRandomGrid(string xyzFile, double side, ParticleInfo part, int nParticles)
{
    ofstream xyz;
    xyz.open(xyzFile, ofstream::out);
    if (xyz.good())
    {
        xyz << nParticles << endl;
        xyz << "Random cube grid of " << part.getName() << ", side=" << side << endl;
        srand((unsigned int)time(NULL));
        
        for (int i = 0; i < nParticles; i++)
        {
            double x = - side / 2 + boundaryDistance + ((double)rand() / RAND_MAX) * (side - 2 * boundaryDistance);
            double y = - side / 2 + boundaryDistance + ((double)rand() / RAND_MAX) * (side - 2 * boundaryDistance);
            double z = - side / 2 + boundaryDistance + ((double)rand() / RAND_MAX) * (side - 2 * boundaryDistance);
            
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

void Container::generateRandomVelocities(string xyzFile, double maxVelocity, ParticleInfo part, int nParticles)
{
    ofstream xyz;
    xyz.open(xyzFile, ofstream::out);
    if (xyz.good())
    {
        xyz << nParticles << endl;
        xyz << "Random velocities of " << part.getName() << endl;
        srand((unsigned int)time(NULL));
        
        for (int i = 0; i < nParticles; i++)
        {
            double x = ((double)rand() / RAND_MAX) * maxVelocity;
            double y = ((double)rand() / RAND_MAX) * maxVelocity;
            double z = ((double)rand() / RAND_MAX) * maxVelocity;
            
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

void Container::model(double timeStep, double time, CoulombCalc calc, OutputMode outputMode, const string& outputFile)
{
    this->calc = calc;
    this->outputMode = outputMode;
    this->timeStep = timeStep;
    
    if (calc == yavorsky || calc == statistics)
    {
        hierarchy = vector<vector<Cell*>>(N);
        interactingCells = vector<vector<Cell*>>(N);
        generateCells();
        defineParticlesSets();
        
        if (calc == statistics)
        {
            Cell::statisticsFile = "/users/vlad/statistics.dat";
            ofstream stat;
            stat.open(Cell::statisticsFile, ofstream::out);
            stat.close();
        }
    }
    
    if (outputMode == xyzFile)
    {
        movie.open(outputFile, ofstream::out);
        movie << setprecision(10);
        
        if (movie.good())
            printCurrentState();
        else
            return;
    }
    else if (outputMode == dcdFile)
    {
    }
    
    for (double t = 0; t <= time; t += timeStep)
    {
        oneStep();
        //cout << "Step #" << (int)t+1 << " finished\n";
        if (shouldOutput(t))
        {
            if (outputMode == dcdFile)
                writeDCDFrame();
            else if (outputMode == xyzFile)
                printCurrentState();
        }
    }
    
    if (calc == yavorsky || calc == statistics)
    {
        delete cell;
    }
}

void Container::oneStep()
{
    vector<Vect3> forces(N);
    
    //calculate force for each particle
    //to use the second newton's law
    for (int i = 0; i < N; i++)
    {
        if (calc == yavorsky)
        {
            for (int j = 0; j < interactingCells[i].size(); j++)
            {
                Vect3 forceFromCell = interactingCells[i][j]->coulombForce(particles[i]);
                forces[i] += forceFromCell;
            }
            
            Cell* lastCell = hierarchy[i][hierarchy[i].size() - 1];
            list<Particle*>* interactingParticles = lastCell->getParticles();
            
            Vect3 forceFromParticles;
            for (list<Particle*>::iterator j = interactingParticles->begin(); j != interactingParticles->end(); j++)
            {
                Particle p = **j;
                if (!(p == particles[i]))
                    forceFromParticles += particles[i].coulombForce(p);
            }
            forces[i] += forceFromParticles;
        }
        else if (calc == N2)
        {
            for (int j = i + 1; j < N; j++)
            {
                Vect3 force = particles[i].coulombForce(particles[j]);
                forces[i] += force;
                forces[j] -= force;
            }
        }
        else if (calc == statistics)
        {
            for (int j = 0; j < interactingCells[i].size(); j++)
            {
                Cell* interactingCell = interactingCells[i][j];
                
                list<Particle*>* cellParticles = interactingCell->allParticles();
                
                Vect3 forceFromCell = interactingCells[i][j]->coulombForce(particles[i]);
                
                Vect3 forcesSum;
                if (cellParticles)
                    for (list<Particle*>::iterator k = cellParticles->begin(); k != cellParticles->end(); k++)
                        forcesSum += particles[i].coulombForce(**k);
                
                interactingCells[i][j]->addStatistics(particles[i], forcesSum, forceFromCell);
                
                forces[i] += forcesSum;
            }
            Cell* lastCell = hierarchy[i][hierarchy[i].size() - 1];
            list<Particle*>* interactingParticles = lastCell->getParticles();
            
            for (list<Particle*>::iterator j = interactingParticles->begin();
                 j != interactingParticles->end(); j++)
                if (!(**j == particles[i]))
                    forces[i] += particles[i].coulombForce(**j);
        }
        
        //boundary condition
        for (int k = 0; k < edges.size(); k++)
        {
            Vect3* proj = pointProjection(particles[i].getR(), edges[k]);
            double dist = (particles[i].getR() - (*proj)).len();
            if (dist < boundaryDistance)
                forces[i] += reflectForce(particles[i].getR(), *proj);
            delete proj;
        }
    }
    
    for (int i = 0; i < N; i++)
    {
        Vect3 newV = particles[i].getV() + forces[i] * timeStep / particles[i].getM();
        Vect3 newR = particles[i].getR() + newV * timeStep;
        
        /* teleportation
         
        pair<Plane, Vect3>* intersectPair = NULL;
        while ((intersectPair = intersectsEdges(particles[i], newR, newV)) != NULL)
        {
            particles[i].move(intersectPair->second, newV);
            reflect(intersectPair->first, intersectPair->second, newR, newV);
        }
        */
        if (calc != N2)
        {
            for (int j = 0; j < hierarchy[i].size(); j++)
                hierarchy[i][j]->remove(&particles[i]);
            hierarchy[i].resize(0);
        
            particles[i].move(newR, newV);
            cell->hierarchy(&particles[i], hierarchy[i]);
        
            interactingCells[i].resize(0);
            cell->interactingCells(hierarchy[i], interactingCells[i]);
        }
        else
            particles[i].move(newR, newV);
    }
}

void Container::generateCells()
{
    cell = new Cell(Vect3(0, 0, 0), side);
    cell->setRoot(true);
    cell->generateSubcells();
    
}

void Container::defineParticlesSets()
{
    for (int i = 0; i < N; i++)
    {
        cell->hierarchy(&particles[i], hierarchy[i]);
        cell->interactingCells(hierarchy[i], interactingCells[i]);
    }
}

void Container::printHierarchy(int i)
{
    cout << "Hierarchy:" << endl;
    for (int j = 0; j < hierarchy[i].size(); j++)
    {
        for (int k = 0; k < j * 4; k++)
            cout << ' ';
        cout << *hierarchy[i][j] << endl;
    }
}

void Container::printInteracting(int i)
{
    cout << "Interacting cells:" << endl;
    for (int j = 0; j < interactingCells[i].size(); j++)
    {
        cout << *interactingCells[i][j] << endl;
    }
}

void Container::recalcCells(int i)
{
    for (int j = 0; j < hierarchy[i].size(); j++)
        hierarchy[i][j]->remove(&particles[i]);
    hierarchy[i].resize(0);
    
    cell->hierarchy(&particles[i], hierarchy[i]);
    printHierarchy(i);
    
    interactingCells[i].resize(0);
    cell->interactingCells(hierarchy[i], interactingCells[i]);
}


Vect3* Container::pointProjection(const Vect3& point, const Plane& plane)
{
    Vect3 norm = plane.normal();
    Vect3* proj = plane.getIntersectPoint(point, point + norm);
    return proj;
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

bool Container::shouldOutput(double timeFromStart)
{
    return (int)(timeFromStart / timeStep) % 1 == 0;
}

void Container::initializeDCD(char* dcdFileName, double dcdStep)
{
    /*
     this->dcdFileName = dcdFileName;
     void createDCD(DCD* dcd, int atomCount, int frameCount, int firstFrame, float timestep, int dcdFreq, int hazUC, int UCX, int UCY, int UCZ);
     
     createDCD(&dcd, N, nSteps /dcdStep, 1, timeStep, dcdStep, 0, 0, 0, 0);
     dcdOpenWrite(&dcd, dcdFileName);
     dcdWriteHeader(dcd);
     dcdClose(dcd)
     */
}

void Container::writeDCDFrame()
{
    /*
     for (int i = 0; i < N; i++)
     {
     Vect3 r = particles[i].getR();
     dcd.frame.X[i] = r.x;
     dcd.frame.Y[i] = r.y;
     dcd.frame.Z[i] = r.z;
     }
     
     dcdOpenAppend(&dcd, dcdFileName);
     dcdWriteFrame(dcd);
     dcdClose(dcd);
     */
}

void Container::printCurrentState()
{
    movie << N << endl << endl;
    for (int i = 0; i < N; i++)
    {
        movie << particles[i].getName() << ' '
        << particles[i].getR().x << ' '
        << particles[i].getR().y << ' '
        << particles[i].getR().z << ' ' << endl;
    }
}

pair<Plane, Vect3>* Container::intersectsEdges(const Particle& p, const Vect3& newR, const Vect3& newV)
{
    for (int j = 0; j < edges.size(); j++)
    {
        Vect3* intersectPoint = edges[j].segmentIntersectsSquare(p.getR(), newR);
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

