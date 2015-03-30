//
//  Jobs.cpp
//  StanfordAlgorithm
//
//  Created by Thomas Hubert on 29/03/2015.
//  Copyright (c) 2015 Thomas Hubert. All rights reserved.
//

#include "Jobs.h"

// Job
bool Job::cmpDiff(const Job &j1, const Job &j2)
{
    int val1 = j1.w - j1.l;
    int val2 = j2.w - j2.l;
    
    if (val1==val2)
        return j1.w>j2.w;
    else
        return val1>val2;
}
//
bool Job::cmpRatio(const Job &j1, const Job &j2)
{
    double val1 = j1.w*1./j1.l;
    double val2 = j2.w*1./j2.l;
    
    return val1>val2;
}
//

// Jobs
Jobs::Jobs(string filename)
{
    ifstream file(filename);
    
    string line;
    int    N, w, l;
    
    if (file.is_open())
    {
        getline(file, line);
        stringstream ss;
        ss << line;
        ss >> N;
        
        v.reserve(N);
        
        while (getline(file, line))
        {
            stringstream ss;
            ss << line;
            ss >> w;
            ss >> l;
            v.push_back(Job(w, l));
        }
        
        file.close();
    }
    else
        throw "Could not open file: " + filename;
    
    wCTD = computeWCT(CompareRule::DIFF);
    wCTR = computeWCT(CompareRule::RATIO);
}
//
long Jobs::computeWCT(CompareRule CR)
{
    sort(v.begin(), v.end(), CR==CompareRule::DIFF ? Job::cmpDiff : Job::cmpRatio);
    
    int  t=0;
    long s=0;
    for (size_t i=0; i<v.size(); ++i)
    {
        t += v[i].getL();
        s += v[i].getW()*t;
    }
    
    return s;
}
//
void Jobs::testClass()
{
    string dir = "/Users/tkhubert/Documents/Etude/11.AlgorithmsStanford/HW/7.Jobs/";
    string file0 = dir + "test1.txt";
    string file1 = dir + "test2.txt";
    string file2 = dir + "test3.txt";
    string file3 = dir + "jobs.txt";

    vector<string>       files{file0, file1, file2, file3};//, file4, file5};
    vector<vector<long> > res{{31814,31814}, {61545,60213}, {688647,674634}, {69119377652,67311454237}};
    
    for (int i=0; i<files.size(); ++i)
    {
        Jobs j(files[i]);
        cout << j.wCTD << " " << j.wCTR << ", ";
        for (int j=0; j<res[i].size(); ++j)
            cout << res[i][j] << " ";
        cout << endl;
    }
}