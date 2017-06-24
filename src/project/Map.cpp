///*
// * Map.cpp
// *
// *  Created on: April 16, 2016
// *      Author: Eylam Milner 311212419
// *      		Lucas Aids	 324392992
// */
//
//#include "Map.h"
//#include <iostream>
//
//// Map's constructor
//Map::Map(double mapResolution, double robotHeight, double robotWidth)
//{
//	// Initialize robot size
//	this->robotHeight 	= robotHeight;
//	this->robotWidth 	= robotWidth;
//
//	// Initialize map resolution
//	this->mapResolution = mapResolution;
//
//	// Initialize map's highest and width
//	this->height = 0;
//	this->width  = 0;
//}
//
//// Loading map
//void Map::loadMap(const string mapFile)
//{
//	// Decode map file
//	lodepng::decode(pixels, width, height, mapFile);
//
//	// Resize the map vector with the height
//	map.resize(height);
//
//	// Going over all of the GridCells in the map
//	for (unsigned int y = 0; y < height; y++)
//	{
//		// Resizing every GridCell with the given width
//		map[y].resize(width);
//	}
//
//	Point current;
//
//	// Going over all of the GridCells to the height of the map
//	for (unsigned int y = 0; y < height; y++)
//	{
//		// Going over all of the GridCell to the width of the map
//		for (unsigned int x = 0; x < width; x++)
//		{
//			current.y = y;
//			current.x = x;
//
//			// Checking if the current GridCell is occupied
//			map[y][x] = checkIfGridCellIsOccupied(current);
//		}
//	}
//
//	// Print the new map
//	printMap();
//}
//
//// Saving the new map file
//void Map::saveMap(const string mapFile)
//{
//	// Encode map file
//	lodepng::encode(mapFile, pixels, width, height);
//}
//
//// Inflating the map's obstacles
//void Map::inflateObstacles()
//{
//	// Initialize robot size in pixels
//	int robotHeightInPixels = robotHeight / mapResolution;
//	int robotWidthInPixels = robotWidth / mapResolution;
//	int robotSizeInPixels = max(robotHeightInPixels, robotWidthInPixels);
//
//	// Initialize the radius to inflate
//	int inflationRadius = 1.2 * robotSizeInPixels;
//
//	// Resizing inflated map
//	inflotedMap.resize(height);
//
//	// Going over the map GridCells
//	for (unsigned int y = 0; y < height; y++)
//	{
//		// Resizing the each GridCell's width
//		inflotedMap[y].resize(width);
//	}
//
//	// Going over the map GridCells
//	for (unsigned int y = 0; y < height; y++)
//	{
//		// Going over the map GridCells
//		for (unsigned int x = 0; x < width; x++)
//		{
//			// If current GridCell is occupied
//			if (map[y][x])
//			{
//				// Iterating through, according to inflation radius
//				for (int dy = -1 * inflationRadius; dy <= inflationRadius; dy++)
//				{
//					// Iterating through, according to inflation radius
//					for (int dx = -1 * inflationRadius; dx <= inflationRadius; dx++)
//					{
//						// if the current GridCell is to be occupied
//						if (y + dy > 0 && y + dy < height && x + dx > 0 && x + dx < width)
//						{
//							// Mark GridCell as occupied in inflated map
//							inflotedMap[y + dy][x + dx] = true;
//						}
//					}
//				}
//			}
//		}
//	}
//
//	// Resizing the map
//	inflotedPixels.resize(width * height * 4);
//	Point current;
//
//	// Going over all of the GridCells to the height of the map
//	for (unsigned int y = 0; y < height; y++)
//	{
//		// Going over all of the GridCells to the width of the map
//		for (unsigned int x = 0; x < width; x++)
//		{
//			current.y = y;
//			current.x = x;
//
//			// Set the current GridCell occupation
//			setInflotedGridCellIsOccupied(current);
//		}
//	}
//
//	// Print the new inflated map
//	printInflotedMap();
//}
//
//// Checking if a specific GridCell is occupied
//bool Map::checkIfGridCellIsOccupied(Point point)
//{
//	// Initializing GridCell variables
//	int c = (point.y * width + point.x) * 4;
//	int r = pixels[c];
//	int g = pixels[c + 1];
//	int b = pixels[c + 2];
//
//	// If GridCell is occupied
//	if (r == 0 && g == 0 && b == 0)
//	{
//		// return true value to the map
//		return true;
//	}
//
//	// if the GridCell is not occupied, return false value to the map
//	return false;
//}
//
//// Checking if a specific GridCell of the infloted map is occupied
//bool Map::checkIfInflotedMapGridCellIsOccupied(Point point) const
//{
//	return this->inflotedMap[point.y][point.x];
//}
//
//unsigned int Map::getWidth() const
//{
//	return this->width;
//}
//
//unsigned int Map::getHeight() const
//{
//	return this->height;
//}
//
//double Map::getMapResolution() const
//{
//	return this->mapResolution;
//}
//
//// Check if a GridCell in the inflated map is occupied
//void Map::setInflotedGridCellIsOccupied(Point point)
//{
//	// Initialize color and GridCell
//	int c = (point.y * width + point.x) * 4;
//	int color = (inflotedMap[point.y][point.x] ? 0 : 255);
//
//	// Set the inflated GridCell color
//	inflotedPixels[c] = color;
//	inflotedPixels[c + 1] = color;
//	inflotedPixels[c + 2] = color;
//	inflotedPixels[c + 3] = 255;
//}
//
//// Print the give map
//void Map::printMap() const
//{
//	// Going over all of the GridCells to the height of the map
// 	for (unsigned int y = 0; y < height; y++)
//	{
// 		// Going over all of the GridCells to the width of the map
//		for (unsigned int x = 0; x < width; x++)
//		{
//			// Print map with occupied or unoccupied GridCells
//			cout << (map[y][x] ? "*" : " ");
//		}
//
//		// Go down one line
//		cout << endl;
//	}
//}
//
//// Print the new inflated map
//void Map::printInflotedMap() const {
//
//	// Going over all of the GridCells to the height of the map
//	for (unsigned int y = 0; y < height; y++)
//	{
// 		// Going over all of the GridCells to the width of the map
//		for (unsigned int x = 0; x < width; x++)
//		{
//			// Print map with occupied or unoccupied GridCells
//			cout << (inflotedMap[y][x] ? "*" : " ");
//		}
//
//		// Go down one line
//		cout << endl;
//	}
//}
//
//Map::~Map()
//{
//	// Going over all of the GridCells to the height of the map
//	for (unsigned int y = 0; y < height; y++)
//	{
//		// Going over all of the GridCells to the width of the map
//		for (unsigned int x = 0; x < width; x++)
//		{
//			// Clear map elements
//			map.clear();
//		}
//	}
//}
//
//// Check if a GridCell in the inflated map is occupied
//void Map::paintGridCell(Point point, int r, int g, int b)
//{
//	// Initialize color and GridCell
//	unsigned int c = (point.y * width + point.x) * 4;
//
//	// Set the inflated GridCell color
//	pixels[c] = r;
//	pixels[c + 1] = g;
//	pixels[c + 2] = b;
//	pixels[c + 3] = 255;
//}
