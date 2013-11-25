//
//  Cell.cpp
//  Coulomb
//
//  Created by Влад Агиевич on 08.11.13.
//  Copyright (c) 2013 Владислав Агиевич. All rights reserved.
//

#include "Cell.h"
#include <cmath>
#include <fstream>

const double Cell::criticalSize = 2;
string Cell::statisticsFile = "";

Cell::Cell(const Vect3& center, const double side)
{
    this->center = center;
    this->side = side;
    this->root = false;
    
    signs = vector<Vect3>(8);
    int xs[] = {1, 1, 1, 1, -1, -1, -1, -1};
    int ys[] = {1, 1, -1, -1, 1, 1, -1, -1};
    int zs[] = {1, -1, 1, -1, 1, -1, 1, -1};
    
    for (int i = 0; i < 8; i++)
        signs[i] = Vect3(xs[i], ys[i], zs[i]);
    
    root = false;
    leaf = false;
    particleList = NULL;
    N = 0;
}

Cell::~Cell()
{
    if (leaf)
        delete particleList;
    else
        for (int i = 0; i < subcells.size(); i++)
            delete subcells[i];
}

void Cell::setRoot(bool root)
{
    this->root = root;
}

bool Cell::isRoot()
{
    return root;
}

bool Cell::operator == (const Cell& other)
{
    return (center == other.center) && (side == other.side);
}

Vect3 Cell::coulombForce(const Particle& p)
{
    if (N == 0)
        return Vect3();
    Particle tmp("", 0, N * avgQ, avgR, Vect3());
    double R = (avgR - p.getR()).len();
    return p.coulombForce(tmp) * G(R, s);
}

void Cell::add(Particle* p)
{
    double newQ = (avgQ * N + p->getQ()) / (N + 1);
    
    if (N != 0)
    {
        D.x = (N - 1) * pow(avgQ / newQ, 2) * D.x / N + pow((avgR.x - (p->getQ() / avgQ) * p->getR().x) / (N + 1), 2);
        D.y = (N - 1) * pow(avgQ / newQ, 2) * D.y / N + pow((avgR.y - (p->getQ() / avgQ) * p->getR().y) / (N + 1), 2);
        D.z = (N - 1) * pow(avgQ / newQ, 2) * D.z / N + pow((avgR.z - (p->getQ() / avgQ) * p->getR().z) / (N + 1), 2);
        
        s.x = sqrt(D.x);
        s.y = sqrt(D.y);
        s.z = sqrt(D.z);
    }
    else
    {
        D = Vect3();
        s = Vect3();
    }
    
    avgR = (avgR * avgQ * N + p->getR() * p->getQ()) / newQ / ( N + 1);
    avgQ = newQ;
    N++;
    
    if (leaf)
        particleList->push_back(p);
}

void Cell::remove(Particle* p)
{
    if (N == 1)
    {
        avgQ = 0;
        D = Vect3();
        s = Vect3();
        avgR = Vect3();
    }
    else{
        double newQ = (avgQ * N - p->getQ()) / (N - 1);
        
        D.x = N * pow(newQ / avgQ, 2) * (D.x - pow((avgR.x - (p->getQ() / avgQ) * p->getR().x) / (N + 1), 2)) / (N - 1);
        D.y = N * pow(newQ / avgQ, 2) * (D.y - pow((avgR.y - (p->getQ() / avgQ) * p->getR().y) / (N + 1), 2)) / (N - 1);
        D.z = N * pow(newQ / avgQ, 2) * (D.z - pow((avgR.y - (p->getQ() / avgQ) * p->getR().z) / (N + 1), 2)) / (N - 1);
        
        s.x = sqrt(D.x);
        s.y = sqrt(D.y);
        s.z = sqrt(D.z);
        
        avgR = (avgR * avgQ * N - p->getR() * p->getQ()) / newQ / ( N - 1);
        avgQ = newQ;
    }
    N--;
    
    if (leaf)
        for (list<Particle*>::iterator i = particleList->begin(); i != particleList->end(); i++)
            if (**i == *p)
            {
                particleList->erase(i);
                break;
            }
}

void Cell::generateSubcells()
{
    if (side / 2 < criticalSize)
    {
        leaf = true;
        particleList = new list<Particle*>;
        return;
    }
    
    subcells = vector<Cell*>(8);
    for (int i = 0; i < 8; i++)
    {
        Vect3 subcellCenter;
        subcellCenter.x = center.x + side / 4 * signs[i].x;
        subcellCenter.y = center.y + side / 4 * signs[i].y;
        subcellCenter.z = center.z + side / 4 * signs[i].z;
        subcells[i] = new Cell(subcellCenter, side / 2);
        subcells[i]->generateSubcells();
    }
}

void Cell::hierarchy(Particle* p, vector<Cell*>& hierarchy)
{

    Vect3 sign = p->getR() - center;
    sign.x = (sign.x == 0) ? 1 : sign.x / abs(sign.x);
    sign.y = (sign.y == 0) ? 1 : sign.y / abs(sign.y);
    sign.z = (sign.z == 0) ? 1 : sign.z / abs(sign.z);
    
    for (int i = 0; i < 8; i++)
        if (sign == signs[i])
        {
            hierarchy.push_back(subcells[i]);
            subcells[i]->add(p);
            if (!subcells[i]->leaf)
                subcells[i]->hierarchy(p, hierarchy);
            break;
        }
    
}

void Cell::interactingCells(const vector<Cell*>& hierarchy, vector<Cell*>& interacting)
{
    static int level = 0;
    
    if (this->isRoot())
        level = 0;
    
    int next;
    for (int i = 0; i < 8; i++)
    {
        if (*(hierarchy[level]) == *(subcells[i]))
            next = i;
        else
            interacting.push_back(subcells[i]);
    }
    level++;
    if (!subcells[next]->subcells.empty())
        subcells[next]->interactingCells(hierarchy, interacting);
}

bool Cell::isLeaf()
{
    return leaf;
}

void Cell::printHierarchy()
{
    static int level = 0;
    
    if (leaf)
    {
        for (int j = 0; j < level * 4; j++)
            cout << ' ';
        cout << particleList->size() << endl;
        return;
    }
    
    for (int i = 0; i < subcells.size(); i++)
    {
        for (int j = 0; j < level * 4; j++)
            cout << ' ';
        cout << i << ' ' << *subcells[i] << endl;
        level++;
        subcells[i]->printHierarchy();
        level--;
    }
}

ostream& operator << (ostream& out, const Cell& c)
{
    out << "center: " << c.center;
    out << " side: " << c.side;
    out << " N: " << c.N;
    out << " charge: " << c.avgQ ;
    out << " r: " << c.avgR;
    return out;
}

list<Particle*>* Cell::getParticles()
{
    return particleList;
}

list<Particle*>* Cell::allParticles()
{
    if (N == 0)
        return NULL;
    if (leaf)
        return particleList;
    
    list<Particle*>* all = new list<Particle*>;
    for (int i = 0; i < subcells.size(); i++)
    {
        list<Particle*>* inSubcell = subcells[i]->allParticles();
        if (inSubcell != NULL)
        {
            all->insert(all->begin(),inSubcell->begin(), inSubcell->end());
            if (!subcells[i]->leaf)
                delete inSubcell;
        }
    }
    return all;
}

void Cell::addStatistics(const Particle& p, const Vect3& honestForce, const Vect3& yavorskyForce)
{
    if (honestForce.allZeros() && yavorskyForce.allZeros())
        return;
    
    ofstream stat;
    
    stat.open(statisticsFile, ofstream::app);
    if (stat.good())
    {
        double coeff = honestForce.len() / yavorskyForce.len();
        double R = (avgR - p.getR()).len();
        stat << R << ' ' << s.x << ' ' << s.y << ' ' << s.z << ' ' << coeff << endl;
        stat.close();
    }
}

double Cell::G(const double R, const Vect3& s)
{
    return 1;
}
