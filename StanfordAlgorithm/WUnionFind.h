//
//  WUnionFind.h
//  StanfordAlgorithm
//
//  Created by Thomas Hubert on 15/02/2015.
//  Copyright (c) 2015 Thomas Hubert. All rights reserved.
//

#ifndef __StanfordAlgorithm__WUnionFind__
#define __StanfordAlgorithm__WUnionFind__

#include <stdio.h>
#include <vector>

using namespace std;

class WUnionFind
{
public:
    WUnionFind(int n);
    int  count() const {return c;}
    int  root     (int p);
    int  connected(int p, int q);
    void unite    (int p, int q);
    
private:
    vector<int> parent;
    vector<int> size;
    int         c;
    
};

#endif /* defined(__StanfordAlgorithm__WUnionFind__) */
