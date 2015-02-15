//
//  Inversion.h
//  AlgorithmsStanford
//
//  Created by Thomas Hubert on 24/01/2015.
//  Copyright (c) 2015 Thomas Hubert. All rights reserved.
//

#ifndef __AlgorithmsStanford__Inversion__
#define __AlgorithmsStanford__Inversion__

#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Inversions
{
public:
    Inversions(string filename);
    Inversions(vector<int>& v);
    
    unsigned long getNbInversions() const { return n;}
    
    static void testClass();
    
private:
    // members
    static const int MIN_SIZE=40;
    unsigned long              n;
    
    // methods
    unsigned long bruteForce     (vector<int>& v) const;
    unsigned long countInversions(vector<int>& v) const;
};

#endif /* defined(__AlgorithmsStanford__Inversion__) */
