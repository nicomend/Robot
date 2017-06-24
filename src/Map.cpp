/*
 * Map.cpp
 *
 *  Created on: April 16, 2016
 *      Author: Eylam Milner 311212419
 *      		Lucas Aids	 324392992
 */
#include <HamsterAPIClientCPP/Hamster.h>
#include "Map.h"
#include "lodepng.h"
#include <iostream>

using namespace HamsterAPI;
// Map's constructor
Map::Map(int robotSize)
{
	this->robotSize = robotSize;
}


// Inflating the map's obstacles
cv::Mat Map::inflateMap(Hamster* hamster) {
	OccupancyGrid ogrid = hamster->getSLAMMap();

	int resulation = ogrid.getResolution() * 100;
	int pixels = robotSize / resulation;
	int width = ogrid.getWidth();
	int height = ogrid.getHeight();
	unsigned char pixel;
	cv::Mat m = cv::Mat(width, height, CV_8UC1);

	// Build the pixel mat
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++) {
			if (ogrid.getCell(i, j) == CELL_FREE)
				pixel = 255;
			else if (ogrid.getCell(i, j) == CELL_OCCUPIED) {
				pixel = 0;
			} else
				pixel = 128;
			m.at<unsigned char>(i, j) = pixel;

			if (pixel == 0) {
				for (int x = i - pixels; x < i + pixels; x++) {
					for (int y = j - pixels; y < j + pixels; y++) {
						m.at<unsigned char>(x, y) = pixel;
					}
				}
			}
		}

	return m;
}



Map::~Map()
{

}

// Check if a cell in the inflated map is occupied
void Map::paintCell(Point point, int r, int g, int b)
{
	// Initialize color and cell
//	unsigned int c = (point.y * width + point.x) * 4;
//
//	// Set the inflated cell color
//	pixels[c] = r;
//	pixels[c + 1] = g;
//	pixels[c + 2] = b;
//	pixels[c + 3] = 255;
}
