//
//  main.cpp
//  AlgorithmsStanford
//
//  Created by Thomas Hubert on 24/01/2015.
//  Copyright (c) 2015 Thomas Hubert. All rights reserved.
//

#include <iostream>
#include "time.h"
#include "Inversion.h"
#include "QuickSortComparisons.h"
#include "MinCutCompression.h"
#include "StronglyConnectedComponent.h"
#include "Dijkstra.h"
#include "TwoSum.h"
#include "MedianMaintenance.h"
#include "Jobs.h"
#include "PrimMST.h"

using namespace std;

int main(int argc, const char * argv[])
{
    clock_t t = clock();
    
    // insert code here...
    //Inversions::testClass();
    //QuickSortComparisons::testClass();
    //MinCutCompression::testClass();
    //SCC::testClass();
    //Dijkstra::testClass();
    //TwoSum::testClass();
    //MedianMaintenance::testClass();
    //Jobs::testClass();
    PrimsMST::testClass();
    
    t = clock() - t;
    cout << "time to compute: "<< float(t)/CLOCKS_PER_SEC << endl;
       
    return 0;
}
