#include "Image.h"
#include "StickerSheet.h"

int main() {

  //I want to be able to call to the image, resize and realign 
  
  Image main_picture, sportscar1, sportscar2, sportscar3;

  main_picture.readFromFile("speed3.png");

  sportscar1.readFromFile("car1.png");

  sportscar1.scale(.3);

  sportscar2.readFromFile("lambo.png");

  sportscar2.scale(.3);

  sportscar3.readFromFile("trip4.png");

  sportscar3.scale(.3);

  StickerSheet * personalsticker = new StickerSheet(main_picture, 3);

  personalsticker->addSticker(sportscar1, 2700, 2850);

  personalsticker->addSticker(sportscar2, 100, 150);

  personalsticker->addSticker(sportscar3, 600, 3550);

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  Image myimage = personalsticker->render();

  myimage.writeToFile("myImage.png");

  delete personalsticker;

  return 0;
}
