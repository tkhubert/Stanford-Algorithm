//
//  Jobs.h
//  StanfordAlgorithm
//
//  Created by Thomas Hubert on 29/03/2015.
//  Copyright (c) 2015 Thomas Hubert. All rights reserved.
//

#ifndef __StanfordAlgorithm__Jobs__
#define __StanfordAlgorithm__Jobs__

#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

enum CompareRule
{
    DIFF,
    RATIO
};
//
class Job
{
public:
    Job(int _w, int _l) : w(_w), l(_l) {}
    static bool cmpDiff (const Job& j1, const Job& j2);
    static bool cmpRatio(const Job& j1, const Job& j2);
    
    int getW() const {return w;}
    int getL() const {return l;}
    
private:
    // members
    int w;
    int l;
};
//
class Jobs
{
public:
    Jobs(string filename);
    
    long computeWCT(CompareRule CR);
    
    static void testClass();
    
private:
    // members
    vector<Job> v;
    
    long        wCTD;
    long        wCTR;
};




#endif /* defined(__StanfordAlgorithm__Jobs__) */
