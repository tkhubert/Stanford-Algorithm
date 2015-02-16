//
//  MinCutCompression.cpp
//  StanfordAlgorithm
//
//  Created by Thomas Hubert on 03/02/2015.
//  Copyright (c) 2015 Thomas Hubert. All rights reserved.
//
#include "MinCutCompression.h"

namespace
{
    const int N_MAX = 1500;
}
//
WUnionFindCompression::WUnionFindCompression(vector<vector<int> >& _neighbors) :
    neighbors(_neighbors)
{
    c = int(neighbors.size());
    parent.resize(c);
    size.resize(c);
    
    for (int i=0; i<c; ++i)
    {
        parent[i] = i;
        size[i]   = 1;
    }
}
//
int WUnionFindCompression::root(int p)
{
    while(p!=parent[p])
    {
        parent[p] = parent[parent[p]];
        p = parent[p];
    }
    return p;
}
//
int WUnionFindCompression::connected(int p, int q)
{
    return root(p)==root(q);
}
//
void WUnionFindCompression::unite(int p, int q)
{
    int rootP = root(p);
    int rootQ = root(q);
    if (rootP==rootQ)
        return;
    
    int rootMin = size[rootP]<size[rootQ] ? rootP : rootQ;
    int rootMax = rootMin==rootQ ? rootP : rootQ;

    parent[rootMin] = rootMax;
    size  [rootMax]+= size[rootMin];
    neighbors[rootMax].insert(neighbors[rootMax].end(), neighbors[rootMin].begin(), neighbors[rootMin].end());
    neighbors[rootMin].clear();
}
//
const vector<int>& WUnionFindCompression::getNeighbors(int p)
{
    return neighbors[root(p)];
}
//
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
    for (int i=0; i<V; ++i)
    {
        for (int j=0; j<adjList[i].size(); ++j)
            adjList[i][j] -=1;
    }
    
    computeMinCut();
}
//
void MinCutCompression::computeMinCut()
{
    srand(0); // srand(time(NULL));
    
    int N = min(N_MAX,int(V*V*log(V)));
    for (int i=0; i<N; ++i)
    {
        currV = V;
        WUnionFindCompression groups = WUnionFindCompression(adjList);

        while (currV>2)
            contract(groups);
        
        int u = groups.root(0);
        const vector<int>& neighbors_u = groups.getNeighbors(u);
        size_t Nu = neighbors_u.size();
        
        int tmpMinCut = 0;
        for (int v=0; v<Nu; ++v)
        {
            if (!groups.connected(u,neighbors_u[v]))
                tmpMinCut++;
        }
        minCut = i==0 ? tmpMinCut : min(minCut, tmpMinCut);
    }
}
//
void MinCutCompression::contract(WUnionFindCompression& groups)
{
    int u = groups.root(rand() % V);
    const vector<int>& neighbors_u = groups.getNeighbors(u);
    size_t Nu = neighbors_u.size();
    
    int v = 0;
    int v_idx = rand() % Nu;
    for (size_t i=0; i<Nu; ++i)
    {
        v = neighbors_u[(v_idx+i) % Nu];
        if (!groups.connected(u, v))
            break;
    }
    
    groups.unite(u, v);
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