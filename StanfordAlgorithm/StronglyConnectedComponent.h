//
//  StronglyConnectedComponent.h
//  StanfordAlgorithm
//
//  Created by Thomas Hubert on 21/02/2015.
//  Copyright (c) 2015 Thomas Hubert. All rights reserved.
//

#ifndef __StanfordAlgorithm__StronglyConnectedComponent__
#define __StanfordAlgorithm__StronglyConnectedComponent__

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <fstream>
#include <sstream>


using namespace std;

enum STATUS
{
    NOT_SEEN,
    SEEN,
    PROCESSED
};

class SCC
{
public:
    SCC(string filename);
    vector<size_t> getGroupsCount() const;
    
    static void testClass();
    
private:
    int V;
    vector<list<int> > adjL;
    vector<list<int> > adjLR;
    
    int orderIdx;
    int groupIdx;
    
    vector<STATUS>     marked;
    vector<int>        order;
    vector<list<int> > groups;
    
    
    void computeSCC();
    void firstPass();
    void secondPass();
};

#endif /* defined(__StanfordAlgorithm__StronglyConnectedComponent__) */
