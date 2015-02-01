//
//  QuickSortComparisons.cpp
//  AlgorithmsStanford
//
//  Created by Thomas Hubert on 30/01/2015.
//  Copyright (c) 2015 Thomas Hubert. All rights reserved.
//

#include "QuickSortComparisons.h"

QuickSortComparisons::QuickSortComparisons(string filename, PivotRule _PR) :
    PR(_PR)
{
    ifstream file(filename);
    
    vector<int> v;
    int i;
    while (file>>i)
        v.push_back(i);
    
    n = countQSComparisons(v.begin(), v.end());
}
//
QuickSortComparisons::QuickSortComparisons(vector<int>& v, PivotRule _PR) :
    PR(_PR)
{
    n = countQSComparisons(v.begin(), v.end());
}
//
vector<int>::iterator QuickSortComparisons::getPivot(vector<int>::iterator start, vector<int>::iterator end) const
{
    switch (PR)
    {
        case FIRST:
            return start;
        case LAST:
            return end-1;
        case MEDIAN_OF_THREE:
        {
            size_t size = distance(start, end);
            vector<int>::iterator first = start;
            vector<int>::iterator last  = end-1;
            vector<int>::iterator med   = start+(size-1)/2;
            
            if ((*first<=*med && *med<=*last) || (*last<=*med && *med<=*first))
                return med;
            else if ((*med<=*first && *first<=*last) || (*last<=*first && *first<=*med))
                return first;
            else
                return last;
        }
        case RANDOM:
        {
            size_t size = distance(start, end);
            return start + (rand() % size);
        }
        default:
            throw "This Pivot Rule is not implemented";
    }
}
//
long QuickSortComparisons::countQSComparisons(vector<int>::iterator start, vector<int>::iterator end) const
{
    size_t size = distance(start, end);
    
    if (size<=1)
        return 0;
    
    iter_swap(start, getPivot(start, end));
    int val = *start;
    
    vector<int>::iterator itr_i = start+1;
    for (vector<int>::iterator itr_j=itr_i; itr_j!=end; ++itr_j)
    {
        if (*itr_j<val)
        {
            iter_swap(itr_j, itr_i);
            itr_i++;
        }
    }
    iter_swap(start, itr_i-1);
    
    long n1 = countQSComparisons(start, itr_i-1);
    long n2 = countQSComparisons(itr_i, end);
    
    return n1 + n2 + size-1;
}
//
void QuickSortComparisons::testClass()
{
    string dir = "/Users/tkhubert/Documents/Etude/11.Algorithms1Stanford/HW/2.QuickSortComparisons/";
    string file0 = dir + "10.txt";
    string file1 = dir + "100.txt";
    string file2 = dir + "1000.txt";
    string file3 = dir + "QuickSort.txt";
    vector<string> files{file0, file1, file2, file3};//, file4, file5};
    vector<vector<long> > res{{25,29,21},{615,587,518},{10297,10184,8921},{162085,164123,138382}};
    
    vector<PivotRule> PRS{PivotRule::FIRST, PivotRule::LAST, PivotRule::MEDIAN_OF_THREE};
    
    for (int i=0; i<files.size(); ++i)
    {
        for (int j=0; j<PRS.size(); ++j)
        {
            QuickSortComparisons QSC(files[i], PRS[j]);
            cout << QSC.getNbComparisons() << " " << res[i][j] << ", ";
        }
        cout << endl;
    }
    
    int nb = 0;
    int NBRUN = 10;
    for (int i=0; i<NBRUN; ++i)
    {
        srand(i);
        QuickSortComparisons QSC(file3, PivotRule::RANDOM);
        nb += QSC.getNbComparisons();
    }
    cout << "Random pivot:" << nb*1./NBRUN << endl;
}