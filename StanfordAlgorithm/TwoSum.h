//
//  TwoSum.h
//  StanfordAlgorithm
//
//  Created by Thomas Hubert on 07/03/2015.
//  Copyright (c) 2015 Thomas Hubert. All rights reserved.
//

#ifndef __StanfordAlgorithm__TwoSum__
#define __StanfordAlgorithm__TwoSum__

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <set>

using namespace std;

class TwoSum
{
public:
    TwoSum(string filename);
    
    long getNbTwoSum() const {return n;}
    static void testClass();
    
private:
    //members
    static const int nbBuckets = 1000133;
    
    int                 n;
    vector<list<long> > hashTable;
    
    
    //methods
    int hash(long x) const;
    int countNbTwoSumHash(const vector<long>& v);
    int countNbTwoSum(vector<long>& v);
    
};

#endif /* defined(__StanfordAlgorithm__TwoSum__) */
