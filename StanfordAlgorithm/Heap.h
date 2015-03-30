//
//  Heap.h
//  StanfordAlgorithm
//
//  Created by Thomas Hubert on 29/03/2015.
//  Copyright (c) 2015 Thomas Hubert. All rights reserved.
//

#ifndef __StanfordAlgorithm__Heap__
#define __StanfordAlgorithm__Heap__

#include <stdio.h>
#include <vector>

using namespace std;

class Heap
{
public:
    Heap(int N);
    
    bool    contains  (int u) const {return qp[u]!=-1;}
    double  priorityOf(int u) const {return priority[qp[u]];}
    int     getMin()          const {return pq[0];}
    
    void deleteMin();
    void deleteElement(int u);
    void insertElement(int u, double p);
    void chgPriorityOf(int u, double p);
    
private:
    // members
    int size;
    int sizeMax;
    
    // u = pq[idx]
    // idx = qp[u]
    // p = priority[idx] = priority[qp[u]]
    vector<int>    pq;
    vector<int>    qp;
    vector<double> priority;
    
    // methods
    void exch(int idx0, int idx1);
    void swim(int idx);
    void sink(int idx);
};
//

#endif /* defined(__StanfordAlgorithm__Heap__) */
