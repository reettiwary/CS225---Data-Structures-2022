
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  
  /*
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  */

  PNG png_final;

  png_final.readFromFile("tests/pacman.png");

  FloodFilledImage image(png_final);

  BFS bfs(png_final, Point(80,20), .5);

  DFS dfs(png_final, Point(80, 20), .6);

  MyColorPicker xx1;

  MyColorPicker xx2;

  image.addFloodFill(bfs, xx1);
  image.addFloodFill(dfs, xx2);

  Animation animation = image.animate(1000);

  PNG lastframe = animation.getFrame(animation.frameCount() - 1);

  lastframe.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");

  return 0; 
}
