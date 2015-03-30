//
//  PrimMST.h
//  StanfordAlgorithm
//
//  Created by Thomas Hubert on 29/03/2015.
//  Copyright (c) 2015 Thomas Hubert. All rights reserved.
//

#ifndef __StanfordAlgorithm__PrimMST__
#define __StanfordAlgorithm__PrimMST__

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include "Heap.h"

using namespace std;

class UWEdge
{
public:
    UWEdge() : u(-1), v(-1), w(-1) {}
    UWEdge(int _u, int _v, double _w) : u(_u), v(_v), w(_w) {}
    
    int    getU() const {return u;}
    int    getV() const {return v;}
    double getW() const {return w;}
    
private:
    int    u;
    int    v;
    double w;
};
//
class PrimsMST
{
public:
    PrimsMST(string filename, bool startAt0=false);
    
    static void testClass();
    
private:
    // members
    int V;
    int E;
    vector<list<UWEdge> > adjL;
    
    double maxWeight;
    double mstWeight;
    
    // methods
    void ComputeMSTWeight();
};

#endif /* defined(__StanfordAlgorithm__PrimMST__) */
