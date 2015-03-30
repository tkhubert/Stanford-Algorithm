//
//  PrimMST.cpp
//  StanfordAlgorithm
//
//  Created by Thomas Hubert on 29/03/2015.
//  Copyright (c) 2015 Thomas Hubert. All rights reserved.
//

#include "PrimMST.h"

PrimsMST::PrimsMST(string filename, bool startAt0)
{
    ifstream file(filename);
    
    int u, v;
    double w;
    string line;
    
    maxWeight = 0;
    if (file.is_open())
    {
        getline(file, line);
        stringstream ss;
        ss << line;
        ss >> V;
        ss >> E;
        adjL.resize(V);
        
        while (getline(file, line))
        {
            stringstream ss;
            ss << line;
            ss >> u;
            ss >> v;
            ss >> w;
            maxWeight = max(w, maxWeight);
            
            if (!startAt0)
            {
                u--;
                v--;
            }
            UWEdge e(u, v, w);
            adjL[u].push_back(e);
            adjL[v].push_back(e);
        }
        maxWeight++;
        
        file.close();
    }
    else
        throw "Could not open file: " + filename;

    ComputeMSTWeight();
}
//
void PrimsMST::ComputeMSTWeight()
{
    Heap h(V);
    int source=0;
    
    for (int t=0; t<V; ++t)
        if (t!=source)
            h.insertElement(t, maxWeight);
    
    const list<UWEdge>& l = adjL[source];
    for (list<UWEdge>::const_iterator itr=l.begin(); itr!=l.end(); ++itr)
    {
        int    u1 = itr->getU();
        int    u2 = itr->getV();
        int    v  = source == u1 ? u2 : u1;
        double w  = itr->getW();
        h.chgPriorityOf(v, w);
    }
    
    mstWeight=0;
    
    for (int t=1; t<V; ++t)
    {
        int    u = h.getMin();
        double w = h.priorityOf(u);
        h.deleteMin();
        
        mstWeight += w;
        
        const list<UWEdge>& l = adjL[u];
        for (list<UWEdge>::const_iterator itr=l.begin(); itr!=l.end(); ++itr)
        {
            int u1 = itr->getU();
            int u2 = itr->getV();
            int v  = u == u1 ? u2 : u1;
            
            if (h.contains(v))
            {
                double w  = itr->getW();
                double p  = h.priorityOf(v);
                
                if (w<p)
                    h.chgPriorityOf(v, w);
            }
        }
    }
}
//
void PrimsMST::testClass()
{
    string dir = "/Users/tkhubert/Documents/Etude/11.AlgorithmsStanford/HW/7.PrimMST/";
    string file0 = dir + "test1.txt";
    string file1 = dir + "test2.txt";
    string file2 = dir + "test3.txt";
    string file3 = dir + "test4.txt";
    string file4 = dir + "edges.txt";
    
    vector<string> files{file0, file1, file2, file3, file4};
    vector<int>    res{7, -16, 6, 4, -3612829};
    for (int i=0; i<files.size(); ++i)
    {
        PrimsMST pMST(files[i]);
        cout << int(pMST.mstWeight) << " " << res[i] << endl;
    }
    cout << endl;

    vector<double> res2{1.81, 10.46351, 20.7732, 65.24072, 647.663};
    files[0] = dir + "smallEWG.txt";
    files[1] = dir + "mediumEWG.txt";
    files[2] = dir + "1000EWG.txt";
    files[3] = dir + "10000EWG.txt";
    files[4] = dir + "largeEWG.txt";
    for (int i=0; i<files.size(); ++i)
    {
        PrimsMST pMST(files[i], true);
        cout << pMST.mstWeight << " " << res2[i] << endl;
    }
}