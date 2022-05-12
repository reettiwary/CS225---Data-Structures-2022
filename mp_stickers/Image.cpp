#include <cmath>
#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

using cs225::PNG;
using cs225::HSLAPixel;

void Image::lighten(){

    //set a for loop to be able to access .l parameters and sets
    for(double x = 0; x < width(); x++){
        for(double y = 0; y < height(); y++){

            HSLAPixel & val = getPixel(x, y);

            if(val.l <= .9){
                val.l = val.l + .1;
            }

            else{
                val.l = 1;
            }

        }
    }
}


void Image::lighten(double amount){

    //set a for loop to be able to access .l parameters and sets keeping double amount in mind per say

    for(double x = 0; x < width(); x++){
        for(double y = 0; y < height(); y++){

            HSLAPixel & val1 = getPixel(x, y);

        //conditional statement to go through the conditionals of double amount
            if(val1.l <= 1 - amount){
                val1.l = val1.l + amount;
            }

            else{
                val1.l = 1;
            }
        }
    }
}

void Image::darken(){

    //set a for loop to be able to access .l parameters and sets keeping double amount in mind per say and utilize the darken function

    for(double x = 0; x < width(); x++){
        for(double y = 0; y < height(); y++){

            HSLAPixel & val2 = getPixel(x, y);

        //conditional statement to go through the conditionals of double amount
            if(val2.l >= .1){
                val2.l = val2.l - .1;
            }

            else{
                val2.l = 0;
            }
        }
    }
}

//darken double amount function
void Image::darken(double amount){
    for(double x = 0; x < width(); x++){
        for(double y = 0; y < height(); y++){

            HSLAPixel & val3 = getPixel(x, y);

            if(val3.l >= amount){
                val3.l = val3.l - amount;
            }

            else{
                val3.l = 0;
            }
        }
    }
}

//saturate function being utilized with for loops and conditionals
void Image::saturate(){
    for(double x = 0; x < width(); x++){
        for(double y = 0; y < height(); y++){

            HSLAPixel & val4 = getPixel(x, y);

            if(val4.s <= .9){
                val4.s = val4.s + .1;
            }

            else{
                val4.s = 1;
            }
        }
    }
}

void Image::saturate(double amount){
    for(double x = 0; x < width(); x++){
        for(double y = 0; y < height(); y++){

            HSLAPixel & val5 = getPixel(x, y);

            if(val5.s <= 1 - amount){
                val5.s = val5.s + amount;
            }

            else{
                val5.s = 1;
            }
        }
    }
}

//utilize the same idea with the desaturate function
void Image::desaturate(){
    for(double x = 0; x < width(); x++){
        for(double y = 0; y < height(); y++){

            HSLAPixel & val6 = getPixel(x, y);

            if(val6.s >= .1){
                val6.s = val6.s - .1;
            }

            else{
                val6.s = 0;
            }
        }
    }
}

void Image::desaturate(double amount){
    for(double x = 0; x < width(); x++){
        for(double y = 0; y < height(); y++){

            HSLAPixel & val7 = getPixel(x, y);

            if(val7.s >= amount){
                val7.s = val7.s - amount;
            }

            else{
                val7.s = 0;
            }
        }
    }
}

//grayscale function

void Image::grayscale(){
    for(double x = 0; x < width(); x++){
        for(double y = 0; y < height(); y++){

            HSLAPixel & val8 = getPixel(x, y);
            
            val8.s = 0;
        }
    }
}

//rotate color function 
void Image::rotateColor(double degrees){
    for(double x = 0; x < width(); x++){
        for(double y = 0; y < height(); y++){

            HSLAPixel & val9 = getPixel(x, y);

             if(val9.h + degrees < 0){
                 
                 val9.h = 360 - (std::fmod(std::abs(val9.h + degrees), 360));
             }

             else{
                 val9.h = std::fmod((val9.h +degrees), 360);
             }
        }
    }
}

//imported from the lab_intro that we did

void Image::illinify(){
      double blue = 216; //so we have to store the value of blue as a double as I did with its hue value of 216

      double orange = 11; //similar to the blue initialization 

      int average = ((blue - orange) / 2); //now I need the average between both hue values and since blue is a bigger value I would initialize the variable average

      int total_orange = (orange + 360); //because hue is stored as a circle method with 360 degrees in mind I want to add the hue value of orange with 360

      int average2 = ((total_orange - blue) / 2); //now I am going to create a new average value with the bigger value of orange and subtract that with blue's

      int orange_max = (orange + average); //now I will maximize the value of orange in addition to its hue with the original average I found 

      int blue_max = (blue + average2); // I will utilize that same method with blue and average2

      //utilized the nested for loop here

      for(double x = 0; x <width(); x++){
          for(double y = 0; x <height(); y++){

            HSLAPixel & val10 = getPixel(x,y);

            //then I set a conditional statement where I see if pixel.h's value is less than the max value of orange or if it is greater than the max value of blue's hue 
            if(val10.h < orange_max || val10.h > blue_max){
                val10.h = orange; //then the backdrop of the image should be the hue of orange
            }

            //else if conditional statement if the pixel.h value is greater than or equal to the max value of orange and it is less than or equal to the max value of blue 
            else if(val10.h >= orange_max && val10.h <= blue_max){
                val10.h = blue; //then the backdrop of the image should be the hue of blue
            }
         }
      }
}

//scale double factor function with references to the width and height 
void Image::scale(double factor){

    double new_w = this->width();

    double new_h = this->height();

    PNG old_i(*this); 

    this->resize(new_w*factor, new_h*factor);

    for(double x = 0; x < this->width(); x++){
         for(double y = 0; y < this->height(); y++){

             HSLAPixel & val11 = old_i.getPixel(x/factor, y/factor);

             this->getPixel(x,y) = val11;
         }
    }
}

//scale unsigned w, unsigned h function 
void Image::scale(unsigned w, unsigned h){

    double factorw = (double)(w)/(double)(width());

    double factorh = (double)(h)/(double)(height());

    double factornew;

    //set conditional statement here
    if(factorw < factorh){
        factornew = factorw; 
    }

    else{
        factornew = factorh;
    }

    scale(factornew);
}