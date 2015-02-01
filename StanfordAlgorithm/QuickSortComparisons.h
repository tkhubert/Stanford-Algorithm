//
//  QuickSortComparisons.h
//  AlgorithmsStanford
//
//  Created by Thomas Hubert on 30/01/2015.
//  Copyright (c) 2015 Thomas Hubert. All rights reserved.
//

#ifndef __AlgorithmsStanford__QuickSortComparisons__
#define __AlgorithmsStanford__QuickSortComparisons__

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

enum PivotRule
{
    FIRST,
    LAST,
    MEDIAN_OF_THREE,
    RANDOM
};
//

class QuickSortComparisons
{
public:
    QuickSortComparisons(string filename, PivotRule PR);
    QuickSortComparisons(vector<int>& v , PivotRule PR);
    long getNbComparisons() const {return n;}
    
    static void testClass();
    
private:
    // members
    PivotRule PR;
    long      n ;
    
    // methods
    long   countQSComparisons(vector<int>::iterator start, vector<int>::iterator end) const;
    vector<int>::iterator getPivot(vector<int>::iterator start, vector<int>::iterator end) const;
    
};

#endif /* defined(__AlgorithmsStanford__QuickSortComparisons__) */
