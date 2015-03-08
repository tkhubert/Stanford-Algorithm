//
//  TwoSum.cpp
//  StanfordAlgorithm
//
//  Created by Thomas Hubert on 07/03/2015.
//  Copyright (c) 2015 Thomas Hubert. All rights reserved.
//

#include "TwoSum.h"

TwoSum::TwoSum(string filename)
{
    ifstream file(filename);
    
    if (file.is_open())
    {
        vector<long> v;
        long i;
        while (file>>i)
            v.push_back(i);
        
        n = countNbTwoSumHash(v);
        
        file.close();
    }
    else
        throw "Could not open file: " + filename;
}
//
int TwoSum::countNbTwoSum(vector<long>& v)
{
    sort(v.begin(), v.end() );
    v.erase(unique(v.begin(), v.end()), v.end() );
    
    size_t s = 0;
    size_t e = v.size()-1;
    set<int> sFound;
    
    while (s<e)
    {
        long val = v[s] + v[e];
        if (val<-10000)
            ++s;
        else if (val>10000)
            --e;
        else
        {
            sFound.insert(int(val));
            
            size_t t = e-1;
            while (s<t)
            {
                long val2 = v[s] + v[t];
                if (val2>=-10000)
                {
                    sFound.insert(int(val2));
                    --t;
                }
            }
            s++;
        }
    }
    
    return int(sFound.size());
}
//
int TwoSum::hash(long x) const
{
    return ((x % nbBuckets) + nbBuckets) % nbBuckets;
}
//
int TwoSum::countNbTwoSumHash(const vector<long> &v)
{
    hashTable.resize(nbBuckets);
    for (size_t i=0; i<v.size(); ++i)
    {
        int h = hash(v[i]);
        hashTable[h].push_back(v[i]);
    }
    
    int count = 0;
    for (int t=-10000; t<=10000; ++t)
    {
        bool found = false;
        for (int i=0; i<v.size(); ++i)
        {
            long val = t-v[i];
            int  h   = hash(val);
            
            const list<long>& l = hashTable[h];
            if (!l.empty())
            {
                for (list<long>::const_iterator itr=l.begin(); itr!=l.end(); ++itr)
                {
                    if (*itr==val && *itr!=v[i])
                    {
                        count++;
                        found = true;
                        break;
                    }
                }
            }
            if (found)
                break;
        }
    }
    return count;
}

void TwoSum::testClass()
{
    string dir = "/Users/tkhubert/Documents/Etude/11.Algorithms1Stanford/HW/6.TwoSum/";
    string file0 = dir + "test0.txt";
    string file1 = dir + "test1.txt";
    string file2 = dir + "2sum.txt";
    vector<string> files{file0, file1, file2};
    vector<long>    res{11, 6, 427};
    for (int i=0; i<files.size(); ++i)
    {
        TwoSum tS(files[i]);
        cout << tS.getNbTwoSum() << " " << res[i] << endl;
    }
}