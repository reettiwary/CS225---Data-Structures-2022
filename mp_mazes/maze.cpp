/* Your code here! */

#include "maze.h"
#include "dsets.h"
#include "cs225/PNG.h"
#include <vector>
#include <queue>
#include <stack>
#include "cs225/HSLAPixel.h"

using namespace cs225;
using namespace std;

SquareMaze::SquareMaze(){ 

    width1 = 0; //initialize my width to 0

    height1 = 0; //same with height
    
    size1 = 0; //same with size 
}

void SquareMaze::setWall(int x, int y, int dir, bool exists){

    int strmult = y*width1; 

    int sum_orig = x + strmult;

    if(dir == 0){

        rghtdwn[sum_orig].first = exists;
    }

    if(dir == 1){

        rghtdwn[sum_orig].second = exists;
    }
}

void SquareMaze::makeMaze(int width, int height){

    width1 = width; //now I am setting my width to the given width

    height1 = height; //same with height

    size1 = (width1 * height1); //size's formula will be new val at width times the new height

    sets_.addelements(size1); //so for each maze part which will be coded into, we want to call the
                             //separate disjoint set 

    for(int x = 0; x < size1; x++){ //++x 
        
        rghtdwn.push_back(pair<bool, bool> (true, true)); //essentially the for loop will push back with the vector bool reference 

    }

    while(sets_.size(0) != size1){ //now a while loop which will compare and continue to through code until the sets_.size(0) is equal 
                                   //intial val at size, we want to be able to gain one set from the 
                                   //disjoint that stores all or most elements 


        int a = rand()%width1; //call to rand and modulo with width val

        int b = rand()%height1; //same with height

        bool mid_r = rand()%2; //now modulo


        int var_1 = b * width1;

        int sum1 = a + var_1;

        int curval = sum1; //setting the current value of mod height times width plus mod width


        int var_2 = a + 1;

        int var_3 = b * width1;

        int sum2 = var_2 + var_3;

        int cur_rght = sum2; //similar idea but now I want the current value at the right to be incremented by 1 width wise



        int var_4 = b + 1;

        int var_5 = var_4 * width1;

        int sum3 = a + var_5;

        int cur_dwn = sum3; //I want to repeat the same idea but now my current value at the downwards scope being incremented by 1 and still being mulitiplied


        if(mid_r){ //conditional statement to see that if the mod is called

            int width_dec = width1 - 1; //setting width to decrement by 1 (-- doesnt work)


            if(a < width_dec && rghtdwn[curval].first){ //nested if statements to check and see

                //if(sets_.find(curval) == sets_.find(cur_rght)){

                    //setWall(a, b, 0, true);

                if(sets_.find(curval) != sets_.find(cur_rght)){
                    
                    setWall(a, b, 0, false);

                    sets_.setunion(curval, cur_rght);
                }
            }
        }
        
        else{ //check with the current value downwards here 

            int height_dec = height1 - 1; //same idea as we did with the width

            if(b < height_dec && rghtdwn[curval].second){

                //repeating the same thing except now I replace with the down current val

                if(sets_.find(curval) != sets_.find(cur_dwn)){

                    //setWall(a, b, 0, true);

                    //setWall(a, b, 0, false);

                    setWall(a, b, 1, false);

                    sets_.setunion(curval, cur_dwn);
                }
            }
        }
    }

}

bool SquareMaze::canTravel(int x, int y, int dir) const{

    //if(dir == 1){ 
    if(dir == 0){ //0 goes to the right direction

        int width_dec = width1 - 1;

        int var_6 = y * width1;

        int sum4 = x + y * width1;

        if(!rghtdwn[sum4].first && x < width_dec){

            return true;
        }
    }

    //if(dir == 0){ 
    if(dir == 1){ //1 goes downwards

        int height_dec = height1 - 1;

        int var_7 = y * width1;

        int sum5 = x + y * width1;

        if(!rghtdwn[sum5].second && y < height_dec){

            return true;
        }
    }

    if(dir == 2){ // 2 goes to the left 

        int x_dec = x - 1;

        int var_8 = y * width1;

        int sum6 = x_dec + var_8;

        if(!rghtdwn[sum6].first && x > 0) {

            return true;
        }
    }

    if(dir == 3){ // 3 goes up

        int y_dec = y - 1;

        int var_9 = y_dec * width1;

        int sum7 = x + var_9;

        if(!rghtdwn[sum7].second && y > 0) {

            return true;
        }
    }

    return false;
}


//bool canTravel(int x, int y, int dir) const;

        //void setWall(int x, int y, int dir, bool exists);

        //std::vector<int> solveMaze();

        //vector<int> solveMaze();

        //PNG * drawMaze() const;

        //PNG * drawMazeWithSolution();

   // private:

       // int width1;

       // int height1;

       // int size1;

       // DisjointSets sets_;

       // vector<pair<bool, bool>> rghtdwn; 

vector<int> SquareMaze::solveMaze(){

    //variable rename (subs)

    vector<int> longdistance;

    vector<int> back1;

    vector<int> length1;

    queue<int> queue1;

    vector<bool> visit1;
    

    back1.resize(size1, -1);

    length1.resize(size1, -1);

    //visit1.resize(size1, true);

    visit1.resize(size1, false);


    queue1.push(0);

    //visit1[0] = false;

    visit1[0] = true;


    while(!queue1.empty()){ //setting a while loop to continue through the code to be able to solve maze

        int c = queue1.front();

        queue1.pop();

        int d = c % width1;

        int e = c / width1;

        int sumc = c + 1;


        //if(canTravel(d, e, 0) && !visit1[sumc] && length1[sumc] == -1 or 0){

        if(canTravel(d, e, 0) && !visit1[sumc] && length1[sumc] != 0){

            length1[sumc] = length1[c] + 1;

            back1[sumc] = c;

            queue1.push(sumc);

            visit1[sumc] = true;
        }


        int sumc_2 = c + width1;

        //if(canTravel(d, e, 1) && !visit1[sumc_2] && length1[sumc_2] == -1 or 0){

        if(canTravel(d, e, 1) && !visit1[sumc_2] && length1[sumc_2] != 0){

            length1[sumc_2] = length1[c] + 1;

            back1[sumc_2] = c;

            queue1.push(sumc_2);

            visit1[sumc_2] = true; 

        }


        int diff = c - 1;

        //if(canTravel(d, e, 2) && !visit1[diff] && length1[diff] == -1 or 0){

        if(canTravel(d, e, 2) && !visit1[diff] && length1[diff] != 0){

            length1[diff] = length1[c] + 1;

            back1[diff] = c;

            queue1.push(diff);

            visit1[diff] = true; 

    }

        int diff_w = c - width1;

        //if(canTravel(d, e, 3) && !visit1[diff_w] && length1[diff_w] == -1 or 0){

        if(canTravel(d, e, 3) && !visit1[diff_w] && length1[diff_w] != 0){

            length1[diff_w] = length1[c] + 1;

            back1[diff_w] = c;

            queue1.push(diff_w);

            visit1[diff_w] = true; 
    }
    
    }

    int lglength1 = 0; //now I am setting a long ditance length reference to 0

    int idx1 = 0; //initializing the idx variable to go through 

    for (int x = size1 - width1; x < size1; x++){ //setting a for loop to go through and see if a path can be derived as long distance towards downwards 

        //if(length1[x] >= lglength1){

        if(length1[x] > lglength1){

            lglength1 = length1[x];

            idx1 = x;
        }
    }


    stack<int> stack1;

    while(idx1){ //while loop to continue and call to stack and push so maze can pass through
        
        if(back1[idx1] == idx1 -1){

            stack1.push(0);
        }

        else if(back1[idx1] == idx1 - width1){

            stack1.push(1);
        }

        else if(back1[idx1] == idx1 + 1){

            stack1.push(2);
        }

        else if(back1[idx1] == idx1 + width1){

            stack1.push(3);
        }

        idx1 = back1[idx1];
    }

    while(!stack1.empty()){ //to see if stack does not equal empty

        longdistance.push_back(stack1.top());

        stack1.pop();
    }

    return longdistance;
}

PNG * SquareMaze::drawMaze() const{

    int var_10 = width1*10;

    int sum8 = var_10 + 1;

    int var_11 = height1*10;

    int sum9 = var_11 + 1;

    PNG * png1 = new PNG(sum8, sum9); //pointer reference with sums etc.

    for(int x = 0; x < sum8; x++){ //nested for loop
    //for(int x = 0; x < width1*10 + 1; ++x){

        for(int y = 0; y < sum9; y++){
        //for(int y = 0; y < height1*10 + 1; ++y){
            
            if(x == 0){

                png1->getPixel(x, y).l = 0;
            }

            
            //if(x > 10 && y == 0){
            if(x > 9 && y == 0){

                png1->getPixel(x,y).l = 0;
            }
        }
    }

    for(int x = 0; x < width1; x++){
    //for(int x = 0; x < width1; ++x){

        for(int y = 0; y < height1; y++){
            //for(int y = 0; y < height1; ++y){

            int var_12 = y*width1;

            int sum10 = x + var_12;

            if(rghtdwn[sum10].first){ //to see the right and down side of a maze square

                for(int z = 0; z < 11; z++){
                //for(int z = 0; z < 11; ++z){

                    int var_13 = x + 1;
                    int var_14 = var_13 * 10;

                    int var_15 = y*10;
                    int var_16 = var_15 + z;

                    png1->getPixel(var_14, var_16).l = 0;
                }
            }

            int sum11 = x + var_12;

            if(rghtdwn[sum11].second){ //looking again at square maze situation

                for(int r = 0; r < 11; r++){
                //for(int r = 0; r < 11; ++r){

                    int var_17 = x*10;
                    int sum12 = var_17 + r;

                    int var_18 = y + 1;
                    int sum13 = var_18*10;

                    png1->getPixel(sum12, sum13).l = 0;
                }
            }
        }
    }

    return png1;
}


PNG * SquareMaze::drawMazeWithSolution(){

    PNG * png2 = drawMaze();

    vector<int>longdistance = solveMaze();

    //int x_ = 2; any number acts funny

    int x_ = 5;

    //int y_ = 2;

    int y_ = 5;


    for(int part = 0; part < int(longdistance.size()); part++){
   // for(int part = 0; part < int(longdistance.size()); ++part){

        if(longdistance[part] == 0){

            for(int z_ = 0; z_ < 11; z_++){
                //for(int z_ = 0; z_ < 11; ++z_){

                int subxz = x_ + z_;
                
                HSLAPixel & pix = png2->getPixel(subxz, y_);

                pix.h = 0; //like previous mps

                pix.s = 1;
                
                pix.l = .5;

                pix.a = 1;
            }

            x_ = x_ + 10;
        }

        else if(longdistance[part] == 1){

            for(int z_ = 0; z_ < 11; z_++){
            //for(int z_ = 0; z_ < 11; ++z_){

                int subzy = z_ + y_;
                
                HSLAPixel & pix = png2->getPixel(x_ , subzy);

                pix.h = 0;

                pix.s = 1;
                
                pix.l = .5;

                pix.a = 1;
            }

            y_ = y_ + 10;
        }

        else if(longdistance[part] == 2){

            for(int z_ = 0; z_ < 11; z_++){

                int decxz = x_ - z_;
                
                HSLAPixel & pix = png2->getPixel(decxz, y_);

                pix.h = 0;

                pix.s = 1;
                
                pix.l = .5;

                pix.a = 1;
            }

            x_ = x_ - 10;
        }
        
        else if(longdistance[part] == 3){

            for(int z_ = 0; z_ < 11; z_++){

                int decyz = y_ - z_;
                
                HSLAPixel & pix = png2->getPixel(x_, decyz);

                pix.h = 0;

                pix.s = 1;
                
                pix.l = .5;

                pix.a = 1;
            }

            y_ = y_ - 10;
        }
    }

    int incx = x_ + 5;

    for(int s = x_ - 4; s < incx; s++){

        int incy = y_ + 5;

        HSLAPixel & pix1 = png2->getPixel(s, incy);

        pix1.l = 1;

        pix1.a = 1;
    }

    return png2;
        
    }