#include "StickerSheet.h"
#include "Image.h"

//
// StickerSheet(const Image & picture, unsigned max);

//     ~StickerSheet();

//     void clear();

//     StickerSheet(const StickerSheet & other);

//     void copy(const StickerSheet & other);

//     const StickerSheet & operator = (const StickerSheet & other);

//     void changeMaxStickers(unsigned max);

//     int addSticker(Image & sticker, unsigned x, unsigned y);

//     bool translate(unsigned index, unsigned x, unsigned y);

//     void removeSticker(unsigned index);

//     Image * getSticker(unsigned index);

//     Image render() const;

//     private:

//     Image main_picture;
//     unsigned max_val;
//     Image ** grid_;
//     unsigned *x_;
//     unsigned *y_;
    //

StickerSheet::StickerSheet(const Image & picture, unsigned max){
    main_picture = picture; //set a variable to hold picture 
    max_val = max; //set the unsigned max to the max_val variable

    grid_ = new Image*[max_val]; //create a grid that carries the pointer to max_val

    //create a for loop which accesses the array of grid that is set to the current value of j 
    //set it to NULL each and every time 
    for(unsigned j = 0; j < max_val; j++){

        grid_[j] = NULL;

    }

    x_ = new unsigned[max_val]; //x_ stores max val through array
    y_ = new unsigned[max_val]; //y_ stores the max val through array
}

StickerSheet::~StickerSheet(){
    clear(); //clear
}

//apply the delete idea for clear and set grid_ = NULL, x_ = NULL, y_ = NULL
void StickerSheet::clear(){

    delete[] grid_; 
    grid_ = NULL;


    delete[] x_;
    x_ = NULL;


    delete[] y_;
    y_ = NULL;

}

StickerSheet::StickerSheet(const StickerSheet & other){
    copy(other); //copy
}

void StickerSheet::copy(const StickerSheet & other){
    main_picture = other.main_picture; //main picture needs to equal to the other.main_picture
    max_val = other.max_val; //max_val equals to other.max_val
    grid_ = new Image*[max_val]; //new pointer reference to Image with max_val

    for(unsigned k = 0; k < max_val; k++){ //for loop with the same idea as how grid_[k] array value refers to NULL unless the max_val is surpassed by k
        grid_[k] = NULL;

    }

    x_ = new unsigned[max_val];
    y_ = new unsigned[max_val];

    //similar idea applied from earlier 
    for(unsigned s = 0; s < max_val; s++){
        grid_[s] = other.grid_[s];
        x_[s] = other.x_[s];
        y_[s] = other.y_[s];
    }
}

const StickerSheet & StickerSheet::operator = (const StickerSheet & other){
    clear();

    copy(other);
    
    return *this; //return pointer reference
}

void StickerSheet::changeMaxStickers(unsigned max){

    //conditional statement to see if the max_val value is equivalent to the max value then return
    if(max_val == max){
        return;
    }

    //std::cout<<"hello 1"<<std::endl;
    Image **newgrid_ = new Image*[max]; //newgrid double pointer reference 

    //for loop with the similar idea with for loop
    for(unsigned t = 0; t < max; t++){
        newgrid_[t] = NULL;
      //  std::cout<<newgrid_[t]<<std::endl;
            //std::cout<<"in the loop"<<std::endl;

    }

   unsigned * x_new = new unsigned[max]; //create new x_new variable holding max through array elements value 
    unsigned * y_new = new unsigned[max]; //similar idea with y_new variable

    //set a conditional statement leading into a for loop
    if(max_val < max){
        for(unsigned t = 0; t < max_val; t++){ //newgrid equals to the grid t times as long as t is less than max_val

        //and as long as max_val is less than max 

            newgrid_[t] = grid_[t];
             //std::cout<<newgrid_[t]<<std::endl;

            //here x_new and y_new will equal to the values of x_ and y_
            x_new[t] = x_[t];
            y_new[t] = y_[t];

              //std::cout<<"in the loop 2"<<std::endl;
        }

        //similar idea applied as earlier however both max_val and max are considered 
        for(unsigned t = max_val; t < max; t++){
            newgrid_[t] = NULL;

              //std::cout<<"in the loop 3"<<std::endl;
        }
    }

    if(max_val > max){
        //greater than factor is now taken into account 

        for(unsigned t = 0; t < max; t++){
            newgrid_[t] = grid_[t];
            x_new[t] = x_[t];
            y_new[t] = y_[t];

              //std::cout<<"in the loop 4"<<std::endl;
        }

        for(unsigned t = max; t < max_val; t++)
        {
            grid_[t] = NULL;
        }
    }

      //std::cout<<"outseeeeeeeeee"<<std::endl;
    clear();

    //here we reassign everything 

    max_val = max;

    grid_ = newgrid_;

    x_ = x_new;

    y_ = y_new;
}

int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y){

      //std::cout<<"in add sticker"<<std::endl;

    for(unsigned a = 0; a < max_val; a++){

        //now we need to refer to &sticker and see what the current value of a is truly being returned as and utilized 

        if(grid_[a] == NULL){

            grid_[a] = &sticker;

            x_[a] = x;

            y_[a] = y;

            return a;
        }
    }

    return -1;

}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){

//here a conditional statement is set to OR and returns a false 
    if(grid_[index] == NULL || index >= max_val){

        return false;
    }

    else{

        //else the index is taken into account by passing in as an array and returning true 
        x_[index] = x;

        y_[index] = y;

        return true;
    }
}

void StickerSheet::removeSticker(unsigned index){ 

    //we wanna see if index is less than max_val then the grid_[index] access will be NULL 
    if(index < max_val){
        grid_[index] = NULL;

    }
}

Image * StickerSheet::getSticker(unsigned index){

    //now we use getSticker to apply the same idea as eariler but if grid_ value at index is equivalent to NULL OR index is greater than or equal to max_val then NULL is returned
    if(grid_[index] == NULL || index >= max_val){

        return NULL;
    }
    return grid_[index]; //and we also return the grid_[index] value 
}

Image StickerSheet::render() const{
      //std::cout<<"render "<<std::endl;

      unsigned xvaluecomp = 0; //I want to be able to set up a temporary xvaluecomparison variable 

      unsigned yvaluecomp = 0; //same with yvaluecomparison variable 
      
      unsigned width_ = main_picture.width(); //here I want to set the new width I call to the main_picture's width 
      //std::cout<<"width1"<<width_<<std::endl;
      
      unsigned height_ = main_picture.height(); //similar idea with the height 
          //std::cout<<"width1"<<std::endl;
                    //std::cout<<"height1"<<height_<<std::endl;

      //set a for loop where we get to access grid_'s value and see if it is not equal to null then the xvaluecomp will take in the 
      //current value of x_ at f and grid_ at f pointing to the width value 

      //we do the same idea with the height 

      for(unsigned f = 0; f < max_val; f++){ 
            if(grid_[f] != NULL){
    
              xvaluecomp = x_[f] + grid_[f]->width();
              yvaluecomp = y_[f] + grid_[f]->height();

              if(xvaluecomp > width_){ //now if the xvaluecomp is greater than the new width I created 
                  width_ = xvaluecomp; //then the new width I created is set to the value that is currently stored at xvaluecomp
              }

            //now this similar idea is applied with yvaluecomp in comparison with height I created 
              if(yvaluecomp > height_){
                  height_ = yvaluecomp;
              }
          }
      }
    
    Image filledpic = main_picture; //now I want to create filled pic which will be equal to my main_picture persay 
    
    filledpic.resize(width_, height_); //filledpic will be resized with the new width and height I created 

    //then I create a for loop to repeat the same idea as above 
    for(unsigned b = 0; b < max_val; b++){
                  //std::cout<<"for"<<std::endl;

        if(grid_[b] != NULL){

            for(unsigned h = 0; h < grid_[b]->width(); h++){ //rather than confusing myself with x and y I used different letters to represent x and y since we were using it alot within this mp
                
                for(unsigned p = 0; p < grid_[b]->height(); p++){ //poses as the y aspect 

                    cs225::HSLAPixel & picsticker_Pixel = grid_[b]->getPixel(h,p); //call to cs225 and HSLAPixel where picsticker_Pixel is being set to grid at b pointing to getPixel at h and p

                    cs225::HSLAPixel & newsticker_Pixel = filledpic.getPixel(x_[b] + h, y_[b] + p); //additionally we do the same thing here to make sure both x values and y values are considered

                    //so conditional if the picsticker_Pixel.a is not equal to 0
                    if(picsticker_Pixel.a != 0){

                        //then the newsticker_Pixel .h,s,l,and a will be set to the picsticker_Pixel and its dimensions 

                        newsticker_Pixel.h = picsticker_Pixel.h;

                        newsticker_Pixel.s = picsticker_Pixel.s;

                        newsticker_Pixel.l = picsticker_Pixel.l;

                        newsticker_Pixel.a = picsticker_Pixel.a;
                    }
                }
            }
        }
    }
    return filledpic; //then we return the filledpic at the end of the day 
}




                //std::cout<<"grid value"<<grid_[b]->width()<<std::endl;
                //std::cout<<"x coordinate value"<<x_[b]<<std::endl;
                //std::cout<<"max_val"<<max_val<<std::endl;
                //std::cout<<"width"<<width_<<std::endl;
               
            //}

           

              //std::cout<<"done"<<std::endl;

    
//                   //std::cout<<"fill loop"<<std::endl;



//                               //std::cout<<"causing probs"<<std::endl;

// }

// //
//  main_picture = picture;
//     max_val = max;
// //