//
//  MedianMaintenance.cpp
//  StanfordAlgorithm
//
//  Created by Thomas Hubert on 07/03/2015.
//  Copyright (c) 2015 Thomas Hubert. All rights reserved.
//

#include "MedianMaintenance.h"

MedianMaintenance::MedianMaintenance(string filename)
{
    ifstream file(filename);
    
    if (file.is_open())
    {
        int i;
        while (file>>i)
        {
            int min, max;
            if (pqMax.empty() && pqMin.empty())
            {
                pushToMax(i);
            }
            else if (pqMin.empty())
            {
                max = getFromMax();
                if (i<max)
                {
                    int e = popFromMax();
                    pushToMax(i);
                    pushToMin(e);
                }
                else
                    pushToMin(i);
            }
            else
            {
                max = getFromMax();
                min = getFromMin();

                if (i<max)
                {
                    pushToMax(i);
                    if (pqMax.size()>pqMin.size()+1)
                        pushToMin(popFromMax());
                }
                else
                {
                    pushToMin(i);
                    if (pqMin.size()>pqMax.size())
                        pushToMax(popFromMin());
                }
            }
            
            medians.push_back(getFromMax());
        }
        
        sum = accumulate(medians.begin(), medians.end(), 0.);
        sum = ((sum % 10000)+10000) % 10000;
        
        file.close();
    }
    else
        throw "Could not open file: " + filename;
}
//
void MedianMaintenance::testClass()
{
    string dir = "/Users/tkhubert/Documents/Etude/11.Algorithms1Stanford/HW/6.Median/";
    string file0 = dir + "test0.txt";
    string file1 = dir + "test1.txt";
    string file2 = dir + "Median.txt";
    vector<string> files{file0, file1, file2};
    vector<long>    res{54, 148, 1213};
    for (int i=0; i<files.size(); ++i)
    {
        MedianMaintenance mm(files[i]);
        cout << mm.getMedianSum() << " " << res[i] << endl;
    }
}