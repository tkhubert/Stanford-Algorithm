//
//  Inversion.cpp
//  AlgorithmsStanford
//
//  Created by Thomas Hubert on 24/01/2015.
//  Copyright (c) 2015 Thomas Hubert. All rights reserved.
//

#include "Inversion.h"

Inversions::Inversions(string filename)
{
    ifstream file(filename);
    
    if (file.is_open())
    {
        vector<int> v;
        int i;
        while (file>>i)
            v.push_back(i);

        n = countInversions(v);
        file.close();
    }
    else
        throw "Could not open file: " + filename;
}
//
Inversions::Inversions(vector<int>& v)
{
    n = countInversions(v);
}
//
unsigned long Inversions::bruteForce(vector<int>& v) const
{
    unsigned long count = 0;
    
    for (int i=0; i<v.size(); ++i)
    {
        for (int j=i+1; j<v.size(); ++j)
        {
            if (v[i]>v[j])
                count++;
        }
    }
    sort(v.begin(), v.end());
    
    return count;
}
//
unsigned long Inversions::countInversions(vector<int>& v) const
{
    size_t fSize = v.size();
    size_t hSize = fSize/2;

    if (fSize<MIN_SIZE)
        return bruteForce(v);
    
    vector<int> v1(v.begin(), v.begin()+hSize);
    vector<int> v2(v.begin()+hSize, v.end());
    unsigned long n1 = countInversions(v1);
    unsigned long n2 = countInversions(v2);
    unsigned long n3 = 0;
    
    vector<int>::iterator itr_l = v1.begin();
    vector<int>::iterator itr_r = v2.begin();
    
    int idx=0;
    while (itr_l!=v1.end() && itr_r!=v2.end())
    {
        if (*itr_l <= *itr_r)
            v[idx++] = *itr_l++;
        else
        {
            n3+= distance(itr_l, v1.end());
            v[idx++] = *itr_r++;
        }
    }
    
    while (itr_l<v1.end())
        v[idx++] = *itr_l++;
    while (itr_r<v2.end())
        v[idx++] = *itr_r++;
    
    return n1 + n2 + n3;
}
//
void Inversions::testClass()
{
    string dir = "/Users/tkhubert/Documents/Etude/11.Algorithms1Stanford/HW/1.Inversions/";
    string file0 = dir + "INPUT500.txt";
    string file1 = dir + "INPUT1000.txt";
    string file2 = dir + "INPUT2000.txt";
    string file3 = dir + "INPUT5000.txt";
    string file4 = dir + "INPUT10000.txt";
    string file5 = dir + "IntegerArray.txt";
    vector<string> files{file0, file1, file2, file3, file4, file5};
    vector<long>    res{62248, 261237, 1001782, 6243161, 24970965,2407905288};
    
    for (int i=0; i<files.size(); ++i)
    {
        Inversions inv(files[i]);
        cout << inv.getNbInversions() << " " << res[i] << endl;
    }
}