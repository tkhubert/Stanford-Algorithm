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

class MinCutCompression
{
public:
    MinCutCompression(string filename);
    
    void computeMinCut();
    int  getMinCut()     const {return minCut;}
    static void testClass();
    
private:
    // members
    size_t               E, currE;
    size_t               V, currV;
    vector<vector<int> > adjList;
    vector<int>          fused;
    
    int                  minCut;
    
    // methods
    void findEdge(int& u, int& v, vector<vector<int> >& adj);
    void contract(vector<vector<int> >& adj);
    void contract(int u, int v, vector<vector<int> >& adj);
};

#endif /* defined(__StanfordAlgorithm__MinCutCompression__) */
