//
//  StronglyConnectedComponent.cpp
//  StanfordAlgorithm
//
//  Created by Thomas Hubert on 21/02/2015.
//  Copyright (c) 2015 Thomas Hubert. All rights reserved.
//

#include "StronglyConnectedComponent.h"

SCC::SCC(string filename)
{
    ifstream file(filename);
    
    string line;
    int    v, w;
    
    if (file.is_open())
    {
        while (getline(file, line))
        {
            stringstream ss;
            ss << line;
            ss >> v;
            ss >> w;
            int M = max(v, w);
            
            if (adjL.size()<M)
            {
                adjL.resize(M);
                adjLR.resize(M);
            }
            adjL[v-1].push_back(w-1);
            adjLR[w-1].push_back(v-1);
        }
        
        file.close();
    }
    else
        throw "Could not open file: " + filename;
    
    V = int(adjL.size());
    orderIdx = V-1;
    groupIdx = 0;
    
    order.resize(V);
    marked.resize(V);
    fill(marked.begin(), marked.end(), NOT_SEEN);
    
    computeSCC();
}
//
vector<size_t> SCC::getGroupsCount() const
{
    vector<size_t> groupsCount(groups.size());
    for (int g=0; g<groups.size(); ++g)
        groupsCount[g] = groups[g].size();
    
    sort(groupsCount.begin(), groupsCount.end(), greater<int>());
    return groupsCount;
}
//
void SCC::firstPass()
{
    stack<int> dfs;
    for (int u=0; u<V; ++u)
    {
        if (marked[u]==NOT_SEEN)
            dfs.push(u);
        else
            continue;
        
        while (!dfs.empty())
        {
            int v = dfs.top();
            const list<int>& lv = adjLR[v];
            
            if (marked[v]==PROCESSED)
            {
                dfs.pop();
                continue;
            }
            else
            {
                bool allMarked = true;
                for (list<int>::const_iterator itr=lv.begin( ); itr!=lv.end(); ++itr)
                    allMarked = allMarked && marked[*itr]!=NOT_SEEN;
                
                if (allMarked)
                {
                    marked[v] = PROCESSED;
                    order[orderIdx--] = v;
                    dfs.pop();
                }
            }
            
            if (marked[v]!=NOT_SEEN)
                continue;
            else
            {
                marked[v] = SEEN;
                for (list<int>::const_iterator itr=lv.begin( ); itr!=lv.end(); ++itr)
                    if (!marked[*itr])
                        dfs.push(*itr);
            }
        }
    }
    fill(marked.begin(), marked.end(), NOT_SEEN);
}
//
void SCC::secondPass()
{
    groups.push_back(list<int>());
    
    stack<int> dfs;
    for (int i=0; i<V; ++i)
    {
        int u = order[i];
        if (marked[u]==NOT_SEEN)
            dfs.push(u);
        else
            continue;
        
        while (!dfs.empty())
        {
            int v = dfs.top();
            const list<int>& lv = adjL[v];
            
            if (marked[v]==PROCESSED)
            {
                dfs.pop();
                continue;
            }
            else
            {
                bool allMarked = true;
                for (list<int>::const_iterator itr=lv.begin(); itr!=lv.end(); ++itr)
                    allMarked = allMarked && marked[*itr]!=NOT_SEEN;
                
                if (allMarked)
                {
                    marked[v] = PROCESSED;
                    groups[groupIdx].push_back(v);
                    dfs.pop();
                }
            }
            
            if (marked[v]!=NOT_SEEN)
                continue;
            else
            {
                marked[v] = SEEN;
                for (list<int>::const_iterator itr=lv.begin(); itr!=lv.end(); ++itr)
                    if (!marked[*itr])
                        dfs.push(*itr);
            }
        }
        
        groupIdx++;
        groups.push_back(list<int>());
    }
}
//
void SCC::computeSCC()
{
    firstPass();
    secondPass();
}
//
void SCC::testClass()
{
    string dir = "/Users/tkhubert/Documents/Etude/11.AlgorithmsStanford/HW/4.StronglyConnectedComponents/";
    string file0 = dir + "test1.txt";
    string file1 = dir + "test2.txt";
    string file2 = dir + "test3.txt";
    string file3 = dir + "SCC.txt";
    //string file4 = dir + "INPUT10000.txt";
    //string file5 = dir + "IntegerArray.txt";
    vector<string> files{file0, file1, file2, file3};//, file4, file5};
    vector<vector<int> > res{{3,3,3,0,0}, {3,3,2,0,0}, {3,2,2,2,1}, {434821, 968, 459, 313, 211}};

    for (int i=0; i<files.size(); ++i)
    {
        SCC scc(files[i]);
        vector<size_t> gCount = scc.getGroupsCount();
        for (int j=0; j<5; ++j)
        {
            if (j>=gCount.size())
                cout << "0,";
            else
                cout << gCount[j] << ", ";
        }
        cout << "  ";
        
        for (int j=0; j<5; ++j)
            cout << res[i][j] << ", ";
        cout << endl;
    }
}
//