/* Your code here! */

#pragma once
#include "dsets.h"
#include <vector>
#include "cs225/PNG.h"

using namespace cs225;
using namespace std;

class SquareMaze{

    public:

        //labeling the public functions as it was given  

        SquareMaze();
        
        void makeMaze(int width, int height);

        bool canTravel(int x, int y, int dir) const;

        void setWall(int x, int y, int dir, bool exists);

        //std::vector<int> solveMaze();

        vector<int> solveMaze();

        PNG * drawMaze() const;

        PNG * drawMazeWithSolution();

    private:

        //variable names I create 

        int width1;

        int height1;

        int size1;

        DisjointSets sets_;

        //use the vector pair references, essentially the pair 

        vector<pair<bool, bool>> rghtdwn; 

};