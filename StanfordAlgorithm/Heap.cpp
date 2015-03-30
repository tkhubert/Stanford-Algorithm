//
//  Heap.cpp
//  StanfordAlgorithm
//
//  Created by Thomas Hubert on 29/03/2015.
//  Copyright (c) 2015 Thomas Hubert. All rights reserved.
//

#include "Heap.h"

Heap::Heap(int N) : size(0), sizeMax(N)
{
    pq.resize(N);
    qp.resize(N);
    priority.resize(N);
    
    fill(qp.begin(), qp.end(), -1);
}
//
void Heap::exch(int idx0, int idx1)
{
    int    u0 = pq[idx0];
    double p0 = priority[idx0];
    
    pq[idx0]       = pq[idx1];
    pq[idx1]       = u0;
    qp[pq[idx0]]   = idx0;
    qp[pq[idx1]]   = idx1;
    priority[idx0] = priority[idx1];
    priority[idx1] = p0;
}
//
void Heap::swim(int idx)
{
    while (idx>0 && priority[idx]<priority[(idx-1)/2])
    {
        exch(idx, (idx-1)/2);
        idx = (idx-1)/2;
    }
}
//
void Heap::sink(int idx)
{
    while (2*idx+1<size)
    {
        int newIdx = 2*idx+1;
        if (newIdx+1<size && priority[newIdx]>priority[newIdx+1])
            newIdx++;
        
        if (priority[idx]<=priority[newIdx])
            break;
        
        exch(idx, newIdx);
        idx = newIdx;
    }
}
//
void Heap::insertElement(int u, double p)
{
    size++;
    pq[size-1]       = u;
    qp[u]            = size-1;
    priority[size-1] = p;
    
    swim(size-1);
}
//
void Heap::deleteMin()
{
    int umin = pq[0];
    
    exch(0, size-1);
    size--;
    sink(0);
    
    qp[umin] = -1;
}
//
void Heap::deleteElement(int u)
{
    int idx = qp[u];
    exch(idx, size-1);
    size--;
    
    if (idx<size)
    {
        swim(idx);
        sink(idx);
    }
    
    qp[u] = -1;
}
//
void Heap::chgPriorityOf(int u, double p)
{
    deleteElement(u);
    insertElement(u, p);
}