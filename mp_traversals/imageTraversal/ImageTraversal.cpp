#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */

 //ImageTraversal * traverse_;

    //Point start1;

    //Point cur1;

    //double tolerance1;

    //PNG png1;

    //std::vector<std::vector<bool>> visited1;

    //

ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */

  traverse_ = NULL;
}

ImageTraversal::Iterator::Iterator(ImageTraversal * traversal, PNG png, Point start, double tolerance){

  traverse_ = traversal;

  png1 = png;

  start1 = start;

  cur1 = start;

  tolerance1 = tolerance;

  visited1.resize(png1.width());

  for(unsigned x1 = 0; x1 < png1.width(); x1++){
    visited1[x1].resize(png1.height());

    for(unsigned y1 = 0; y1 < png1.height(); y1++){
      visited1[x1][y1] = false;
    }
  }
  //return *this;
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */

  visited1[cur1.x][cur1.y] = true;

  while(!traverse_ -> empty() && (visited1[traverse_-> peek().x][traverse_->peek().y] == true)){
    traverse_ -> pop();
  }

  Point rght = Point(cur1.x + 1, cur1.y);

  Point dwn = Point(cur1.x, cur1.y + 1);

  Point lft = Point(cur1.x - 1, cur1.y);
  
  Point up = Point(cur1.x, cur1.y - 1);

  double Change;

  if(rght.x < png1.width() && rght.y < png1.height()){
    if(visited1[rght.x][rght.y] == false){

      Change = calculateDelta(png1.getPixel(start1.x, start1.y), png1.getPixel(rght.x, rght.y));

      if(Change < tolerance1){
        traverse_ -> add(rght);
      }
    }
  }

  if(dwn.x < png1.width() && dwn.y < png1.height()){

    if(visited1[dwn.x][dwn.y] == false){
      Change = calculateDelta(png1.getPixel(start1.x, start1.y), png1.getPixel(dwn.x, dwn.y));

      if(Change < tolerance1){
        traverse_ -> add(dwn);
      }
    }
  }

  if(lft.x < png1.width() && lft.y < png1.height()){

    if(visited1[lft.x][lft.y] == false){
      Change = calculateDelta(png1.getPixel(start1.x, start1.y), png1.getPixel(lft.x, lft.y));

      if(Change < tolerance1){
        traverse_ -> add(lft);
      }
    }
  }

  if(up.x < png1.width() && up.y < png1.height()){
    
    if(visited1[up.x][up.y] == false){
      Change = calculateDelta(png1.getPixel(start1.x, start1.y), png1.getPixel(up.x, up.y));

      if(Change < tolerance1){
        traverse_ -> add(up);
      }
    }
  }

  if(!traverse_->empty()){
    cur1 = traverse_->peek();
  }

  else{
    traverse_ = NULL;
  }

  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  //return Point(0, 0);

  return cur1;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  return !(this->traverse_ == NULL && other.traverse_ == NULL);
}

