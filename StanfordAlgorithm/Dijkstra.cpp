//
//  Dijkstra.cpp
//  StanfordAlgorithm
//
//  Created by Thomas Hubert on 23/02/2015.
//  Copyright (c) 2015 Thomas Hubert. All rights reserved.
//

#include "Dijkstra.h"

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
    int u0 = pq[idx0];
    int p0 = priority[idx0];
    
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
    while (idx>0 && priority[idx]<priority[idx/2])
    {
        exch(idx, idx/2);
        idx = idx/2;
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
void Heap::insertElement(int u, int p)
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
    swim(idx);
    sink(idx);
    
    qp[u] = -1;
}
//
void Heap::chgPriorityOf(int u, int p)
{
    //int idx = qp[u];
    deleteElement(u);
    insertElement(u, p);
    //sink(idx);
    //swim(idx);
}
//
Dijkstra::Dijkstra(string filename)
{
    ifstream file(filename);
    
    int u, v, l;
    string dummy;
    string line;
    
    if (file.is_open())
    {
        while (getline(file, line))
        {
            stringstream ss;
            ss << line;
            ss >> u;
            
            for (int i=0; i<u-1-adjL.size(); ++i)
                adjL.push_back(list<Edge>());
                
            list<Edge> edges;
            while (true)
            {
                ss >> v;
                getline(ss, dummy, ',');
                ss >> l;
                getline(ss, dummy, '\t');
                
                edges.push_back(Edge(u-1, v-1, l));
                if (!ss)
                    break;
            }
            adjL.push_back(edges);
        }
        file.close();
    }
    else
        throw "Could not open file: " + filename;
    
    V = int(adjL.size());
    marked.resize(V);
    path.resize(V);
    pathL.resize(V);
    
    fill(marked.begin(), marked.end(), 0);
    ComputeShortestPath(0);
}
//
void Dijkstra::ComputeShortestPath(int s)
{
    Heap h(V);
    h.insertElement(s, 0);
    
    for (int t=0; t<V; ++t)
    {
        int u     = h.getMin();
        pathL[u]  = h.priorityOf(u);
        marked[u] = 1;
        h.deleteMin();
        
        const list<Edge>& lu = adjL[u];
        for (list<Edge>::const_iterator itr=lu.begin(); itr!=lu.end(); ++itr)
        {
            int v = itr->getTo();
            if (marked[v])
                continue;
            
            int l = itr->getLength();
            int p = pathL[u]+l;
            
            if (!h.contains(v))
            {
                h.insertElement(v, p);
                path[v] = u;
            }
            else
            {
                if (p<h.priorityOf(v))
                {
                    h.chgPriorityOf(v, p);
                    path[v] = u;
                }
            }
        }
    }
}
//
void Dijkstra::testClass()
{
    string dir = "/Users/tkhubert/Documents/Etude/11.Algorithms1Stanford/HW/5.Dijkstra/";
    string file0 = dir + "small.txt";
    string file1 = dir + "medium.txt";
    string file2 = dir + "dijkstraData.txt";
    string file3 = dir + "dijkstraData.txt";

    vector<string> files{file0, file1, file2, file3};
    vector<vector<int> > idx{{1,4}, {1,7}, {10,30,50,80,90,110,130,160,180,190}, {7,37,59,82,99,115,133,165,188,197}};
    vector<vector<int> > res{{0,2}, {0,5}, {3205,2303,3152,982,2018,2317,1820,2403,3027,2596}, {2599,2610,2947,2052,2367,2399,2029,2442,2505,3068}};
    
    for (int i=0; i<files.size(); ++i)
    {
        Dijkstra dj(files[i]);
        for (int j=0; j<idx[i].size(); ++j)
            cout << dj.getPathLengthTo(idx[i][j]-1) << ",";
        cout << "  ";
        
        for (int j=0; j<idx[i].size(); ++j)
            cout << res[i][j] << ",";
        cout << endl;
    }

}