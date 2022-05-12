/* Your code here! */

#pragma once
#include <vector>

using namespace std;

class DisjointSets{
    public:

    //labeling the public functions as it was given but with variable names I create 

        void addelements(int numb); 

        int find(int element1);

        void setunion(int x, int y);

        int size(int element1);

    private:

    //vector reference 

        vector<int> vector1; 
        
};
