/* Your code here! */
#include "dsets.h"
#include <vector>

void DisjointSets::addelements(int numb){

    while(numb > 0){ //creating a while loop so while the number is greater than 0

        vector1.push_back(-1); //it will traverse through the vector and "delete" by 1 

        numb--; //once this happens our current value that is stored within number decreases too

    }
}

int DisjointSets::find(int element1){

    if(vector1[element1] < 0){ //conditional statement to see that if the value at vector 
                              // whether that specific area (call to element) is less than 0

        return element1; //then we return the element value
    }

    else{ //otherwise

        vector1[element1] = find(vector1[element1]); //we set that vector at that value whichever is stored
                                                     //set it to find the value that is at that specification

        return vector1[element1]; //then return value
    }
}

void DisjointSets::setunion(int x, int y){

    int x1 = find(x); //we want to creat a sub variable where we call to the find function and find x

    int y1 = find(y); //similar to y

    if(x1 == y1){ //set a conditional if x1 is the same as/ equivalent to y1
        return;  //return
    }

    //we are comparing size in a sense through the means of vector1 

    if(vector1[x1] <= vector1[y1]){ //another conditional statement we want to see if the vector value at x1 and y1
                                    //if vector value at x1 is less than or equal to vector value at y1

        vector1[x1] = vector1[x1] + vector1[y1]; //then we want to increment and set the vector value at x1 equal to the summation of 
                                                 //vector value at x1 plus the current vector value at y1

        vector1[y1] = x1; //we then set the current value of vector at y1 equal to whatever is stored within x1
    }

    else{ //else
 
        vector1[y1] = vector1[y1] + vector1[x1]; //repeat the same idea except with y1 being incremented

        vector1[x1] = y1; //set the current value of vector at x1 equal to whatever is stored within y1
    }
}

int DisjointSets::size(int element1){

    return -vector1[find(element1)]; //so find what is at current value within element 1 and let the 
                                     //vector access at that value but we return a negative of it
}