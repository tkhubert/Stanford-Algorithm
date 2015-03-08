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
        
        n = countNbTwoSumSort(v);
        
        file.close();
    }
    else
        throw "Could not open file: " + filename;
}
//
int TwoSum::countNbTwoSumHash(const vector<long> &v)
{
    hashTable.resize(nbBuckets);
    for (size_t i=0; i<v.size(); ++i)
    {
        int h = hash(v[i]/DT);
        hashTable[h].push_back(v[i]);
    }
    
    set<int> sT;
    for (size_t i=0; i<v.size(); ++i)
    {
        int h1 = hash((Tmin-v[i])/DT);
        const list<long>& l1 = hashTable[h1];
        for (list<long>::const_iterator itr=l1.begin(); itr!=l1.end(); ++itr)
        {
            long t = *itr+v[i];
            if (t>=Tmin && t<=Tmax && v[i]!=*itr)
                sT.insert(int(t));
        }
        
        int h2 = hash((Tmin-v[i])/DT+1);
        const list<long>& l2 = hashTable[h2];
        for (list<long>::const_iterator itr=l2.begin(); itr!=l2.end(); ++itr)
        {
            long t = *itr+v[i];
            if (t>=Tmin && t<=Tmax && v[i]!=*itr)
                sT.insert(int(t));
        }
    }
    return int(sT.size());
}
//
int TwoSum::countNbTwoSumSort(vector<long>& v)
{
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    
    vector<long>::iterator s = v.begin();
    vector<long>::iterator e = v.end();
    vector<long>::iterator i;
    
    set<int> sT;
    while (s<e)
    {
        long x = *s;
        i = lower_bound(s, e, Tmin-x);
        e = upper_bound(s, e, Tmax-x);
        
        for (vector<long>::iterator itr=i; itr!=e; ++itr)
        {
            if (x!=*itr)
                sT.insert(int(*itr+x));
        }
        s++;
    }
    return int(sT.size());
}
//
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