//
//  MedianMaintenance.h
//  StanfordAlgorithm
//
//  Created by Thomas Hubert on 07/03/2015.
//  Copyright (c) 2015 Thomas Hubert. All rights reserved.
//

#ifndef __StanfordAlgorithm__MedianMaintenance__
#define __StanfordAlgorithm__MedianMaintenance__

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <list>
#include <numeric>

using namespace std;
class MedianMaintenance
{
public:
    MedianMaintenance(string filename);
    int getMedianSum() const {return sum;}
    
    static void testClass();
    
private:
    // members
    int                 sum;
    list<int>           medians;
    priority_queue<int> pqMin;
    priority_queue<int> pqMax;
    
    // methods
    int  getFromMin() const {return -pqMin.top();}
    int  getFromMax() const {return  pqMax.top();}
    int  popFromMin()       {int e=getFromMin(); pqMin.pop(); return e;}
    int  popFromMax()       {int e=getFromMax(); pqMax.pop(); return e;}
    void pushToMin (int i)  {pqMin.push(-i);}
    void pushToMax (int i)  {pqMax.push( i);}
};
#endif /* defined(__StanfordAlgorithm__MedianMaintenance__) */
