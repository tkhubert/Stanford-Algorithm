//
//  MinCutCompression.h
//  StanfordAlgorithm
//
//  Created by Thomas Hubert on 03/02/2015.
//  Copyright (c) 2015 Thomas Hubert. All rights reserved.
//

#ifndef __StanfordAlgorithm__MinCutCompression__
#define __StanfordAlgorithm__MinCutCompression__

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class WUnionFindCompression
{
public:
    WUnionFindCompression(vector<vector<int> >& neighbors);
    
    int                count() const {return c;}
    int                root        (int p);
    int                connected   (int p, int q);
    void               unite       (int p, int q);
    const vector<int>& getNeighbors(int p);
    
private:
    vector<vector<int> > neighbors;
    vector<int>          parent;
    vector<int>          size;
    int                  c;
};
//
class MinCutCompression
{
public:
    MinCutCompression(string filename);
    
    void computeMinCut();
    int  getMinCut()     const {return minCut;}
    static void testClass();
    
private:
    // members
    size_t               V, currV;
    vector<vector<int> > adjList;
    
    int                  minCut;
    
    // methods
    void contract(WUnionFindCompression& groups);
};

#endif /* defined(__StanfordAlgorithm__MinCutCompression__) */
