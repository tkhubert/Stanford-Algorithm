//
//  MinCutCompression.cpp
//  StanfordAlgorithm
//
//  Created by Thomas Hubert on 03/02/2015.
//  Copyright (c) 2015 Thomas Hubert. All rights reserved.
//

#include "MinCutCompression.h"

MinCutCompression::MinCutCompression(string filename)
{
    ifstream file(filename);
    
    string line;
    string sentence;
    int    i;
    
    if (file.is_open())
    {
        while (getline(file, line))
        {
            stringstream ss, oss;
            ss << line;
            ss >> i;
            oss << ss.rdbuf();
            
            vector<int> v;
            v.insert(v.begin(), istream_iterator<int>(oss), istream_iterator<int>());
            adjList.push_back(v);
        }
        
        file.close();
    }
    else
        throw "Could not open file: " + filename;
    
    V = adjList.size();
    fused.resize(V);
    
    E = 0;
    for (int i=0; i<V; ++i)
    {
        E+=adjList[i].size();
        
        for (int j=0; j<adjList[i].size(); ++j)
            adjList[i][j] -=1;
    }
    E /=2;
    
    computeMinCut();
}
//
void MinCutCompression::computeMinCut()
{
    srand(0); // srand(time(NULL));
    
    size_t N = 1000;
    for (int i=0; i<N; ++i)
    {
        currE = E;
        currV = V;
        vector<vector<int> > adj = adjList;
        
        for (int i=0; i<V; ++i)
            fused[i] = i;
        
        while (currV>2)
            contract(adj);
        
        int u;
        for (u=0; u<E; ++u)
            if (fused[u]==u)
                break;
        
        int minCutTmp = 0;
        for (int j=0; j<adj[u].size(); ++j)
            if (adj[u][j]!=u)
                minCutTmp++;
        
        minCut = i==0 ? minCutTmp : min(minCut, minCutTmp);
    }
}
//
void MinCutCompression::findEdge(int& u, int& v, vector<vector<int> >& adj)
{
    int u_idx = rand() % currV;
    
    int count = -1;
    for (int i=0; i<V; ++i)
    {
        if (fused[i]==i)
            count++;
        
        if (count==u_idx)
        {
            u = i;
            break;
        }
    }
    
    int v_idx = rand() % adj[u].size();
    for (int i=0; i<adj[u].size(); ++i)
    {
        v = adj[u][(v_idx+i) % adj[u].size()];
        if (v!=u)
            break;
    }
}
void MinCutCompression::contract(vector<vector<int> >& adj)
{
    int u, v;
    findEdge(u, v, adj);
    contract(u, v, adj);
}
//
void MinCutCompression::contract(int u, int v, vector<vector<int> >& adj)
{
    for (size_t i=0; i<adj[v].size(); ++i)
    {
        int w = adj[v][i];
        
        for (size_t j=0; j<adj[w].size(); ++j)
            if (adj[w][j]==v)
                adj[w][j]=u;
    }
    adj[u].insert(adj[u].end(), adj[v].begin(), adj[v].end());
    adj[v].clear();
    fused[v] = u;
    currV--;
}
//
void MinCutCompression::testClass()
{
    string dir = "/Users/tkhubert/Documents/Etude/11.Algorithms1Stanford/HW/3.MinCutKarger/";
    string file0 = dir + "kargerMinCut.txt";
    string file1 = dir + "8.txt";
    string file2 = dir + "8bis.txt";
    string file3 = dir + "40.txt";
    //string file4 = dir + "INPUT10000.txt";
    //string file5 = dir + "IntegerArray.txt";
    vector<string> files{file0, file1, file2, file3};//, file4, file5};
    vector<long>    res{17, 2, 1, 3};//, 261237, 1001782, 6243161, 24970965,2407905288};
    
    for (int i=0; i<files.size(); ++i)
    {
        MinCutCompression minCut(files[i]);
        cout << minCut.getMinCut() << " " << res[i] << endl;
    }
}
//