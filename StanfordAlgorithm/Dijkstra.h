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

using namespace std;

class Heap
{
public:
    Heap(int N);
    
    bool contains  (int u) const {return qp[u]!=-1;}
    int  priorityOf(int u) const {return priority[qp[u]];}
    int  getMin()          const {return pq[0];}
    
    void deleteMin();
    void deleteElement(int u);
    void insertElement(int u, int p);
    void chgPriorityOf(int u, int p);
    
private:
    // members
    int size;
    int sizeMax;
    
    vector<int> pq;
    vector<int> qp;
    vector<int> priority;
    
    // methods
    void exch(int idx0, int idx1);
    void swim(int idx);
    void sink(int idx);
};
//
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
