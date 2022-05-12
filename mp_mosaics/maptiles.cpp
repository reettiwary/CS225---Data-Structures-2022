/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */

     MosaicCanvas * mosaicportray = new MosaicCanvas(theSource.getRows(), theSource.getColumns());

     vector<Point<3>> nodevars;

     map<Point<3>, TileImage*> convert1;

     for(auto mosaicnew = theTiles.begin(); mosaicnew != theTiles.end(); mosaicnew++){

         Point<3> column1 = convertToXYZ(mosaicnew->getAverageColor());

         convert1[column1] = &(*mosaicnew);

         nodevars.push_back(column1);
     }

     KDTree<3> kdtree(nodevars);

     for(int x = 0; x < mosaicportray->getRows(); x++){
         for(int y = 0; y < mosaicportray->getColumns(); y++){
             
             Point<3> colavg = convertToXYZ(theSource.getRegionColor(x,y));

             Point<3> nearby = kdtree.findNearestNeighbor(colavg);

             mosaicportray->setTile(x, y, convert1[nearby]);
         }
     }

    return mosaicportray;
}

