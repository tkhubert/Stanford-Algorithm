//
//  Dijkstra.h
//  StanfordAlgorithm
//
//  Created by Thomas Hubert on 23/02/2015.
//  Copyright (c) 2015 Thomas Hubert. All rights reserved.
//

#ifndef __StanfordAlgorithm__Dijkstra__
#define __StanfordAlgorithm__Dijkstra__

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include "Heap.h"

using namespace std;

class Edge
{
public:
    Edge() : u(-1), v(-1), l(-1) {}
    Edge(int _u, int _v, int _l) : u(_u), v(_v), l(_l) {}
    
    int getFrom  () const {return u;}
    int getTo    () const {return v;}
    int getLength() const {return l;}
    
private:
    int u;
    int v;
    int l;
};
//
class Dijkstra
{
public:
    Dijkstra(string filename);
    
    void ComputeShortestPath(int s);
    int  getPathLengthTo(int u) const {return pathL[u];}
    static void testClass();
    
private:
    int V;
    
    vector<int>         marked;
    vector<int>         path;
    vector<int>         pathL;
    vector<list<Edge> > adjL;
};

#endif /* defined(__StanfordAlgorithm__Dijkstra__) */
