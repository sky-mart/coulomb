//
//  Cell.cpp
//  Coulomb
//
//  Created by Влад Агиевич on 08.11.13.
//  Copyright (c) 2013 Владислав Агиевич. All rights reserved.
//

#include "Cell.h"
#include <cmath>

const double Cell::criticalSize = 2;

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
    Particle tmp("", 0, avgQ, avgR, Vect3());
    return p.coulombForce(tmp);
}

void Cell::add(const Particle& p)
{
    double newQ = (avgQ * N + p.getQ()) / (N + 1);
    avgR = (avgR * avgQ * N + p.getR() * p.getQ()) / newQ / ( N + 1);
    avgQ = newQ;
    N++;
}

void Cell::remove(const Particle& p)
{
    if (N == 1)
    {
        avgQ = 0;
        avgR = Vect3();
    }
    else{
        double newQ = (avgQ * N - p.getQ()) / (N - 1);
        avgR = (avgR * avgQ * N - p.getR() * p.getQ()) / newQ / ( N - 1);
        avgQ = newQ;
    }
    N--;
}

void Cell::generateSubcells()
{
    if (side / 2 < criticalSize)
        return;
    
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

void Cell::hierarchy(const Particle& p, vector<Cell*>& hierarchy)
{

    Vect3 sign = p.getR() - center;
    sign.x = (sign.x == 0) ? 1 : sign.x / abs(sign.x);
    sign.y = (sign.y == 0) ? 1 : sign.y / abs(sign.y);
    sign.z = (sign.z == 0) ? 1 : sign.z / abs(sign.z);
    
    for (int i = 0; i < 8; i++)
        if (sign == signs[i])
        {
            hierarchy.push_back(subcells[i]);
            subcells[i]->add(p);
            if (!subcells[i]->subcells.empty())
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
    return subcells.empty();
}

void Cell::printHierarchy()
{
    static int level = 0;
    
    if (isLeaf())
        return;
    
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
    out << " charge: " << c.avgQ ;
    out << " r: " << c.avgR;
    return out;
}