//
//  WUnionFind.cpp
//  StanfordAlgorithm
//
//  Created by Thomas Hubert on 15/02/2015.
//  Copyright (c) 2015 Thomas Hubert. All rights reserved.
//

#include "WUnionFind.h"

WUnionFind::WUnionFind(int n)
{
    parent.resize(n);
    size.resize(n);
    c = n;
    
    for (int i=0; i<n; ++i)
    {
        parent[i] = i;
        size[i]   = 1;
    }
}
//
int WUnionFind::root(int p)
{
    while(p!=parent[p])
    {
        parent[p] = parent[parent[p]];
        p = parent[p];
    }
    return p;
}
//
int WUnionFind::connected(int p, int q)
{
    return root(p)==root(q);
}
//
void WUnionFind::unite(int p, int q)
{
    int rootP = root(p);
    int rootQ = root(q);
    if (rootP==rootQ)
        return;
    
    if (size[rootP]<size[rootQ])
    {
        parent[rootP] = rootQ;
        size  [rootQ]+= size[rootP];
    }
    else
    {
        parent[rootQ] = rootP;
        size  [rootP]+= size[rootQ];
    }
}