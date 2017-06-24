/*
 * RobotMap.cpp
 */
#include "RobotMap.h"
#include <HamsterAPIClientCPP/Hamster.h>
#include <iostream>

using namespace HamsterAPI;

// Map's constructor
RobotMap::RobotMap(int robotSize)
{
	this->robotSize = robotSize;
}

int RobotMap::getResulotion() {
	return this->resulotion;
}

bool RobotMap::checkIfGridCellIsOccupied(Point point)
{
	// Initializing GridCell variables
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

	// if the GridCell is not occupied, return false value to the map
	return false;
}

// Checking if a specific GridCell of the infloted map is occupied
bool RobotMap::checkIfInflotedMapGridCellIsOccupied(Point point) const
{

	return ((this->matrix[point.y][point.x][0] == 0) && (this->matrix[point.y][point.x][1]==0) && (this->matrix[point.y][point.x][2]==0));
}

unsigned int RobotMap::getWidth() const
{
	return this->matrix.cols;
}

unsigned int RobotMap::getHeight() const
{
	return this->matrix.rows;
}

// Inflating the map's obstacles
cv::Mat RobotMap::inflateMap(Hamster* hamster) {
	OccupancyGrid ogrid = hamster->getSLAMMap();

	int gridResulation = ogrid.getResolution() * 100;
	this-> resulotion = gridResulation;
	int pixels = robotSize / gridResulation;
	int width = ogrid.getWidth();
	int height = ogrid.getHeight();
	unsigned char pixel[3];
	cv::Mat m = cv::Mat(width, height, CV_8UC3);
	this->matrix = m;
	// Build the pixel mat
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++) {
			if (ogrid.getCell(i, j) == CELL_FREE){
				pixel[0] = 255;
				pixel[1] = 255;
				pixel[2] = 255;
			}
			else if (ogrid.getCell(i, j) == CELL_OCCUPIED) {
				pixel[0] = 0;
				pixel[1] = 0;
				pixel[2] = 0;
			} else {
				pixel[0] = 128;
				pixel[1] = 128;
				pixel[2] = 128;
			}
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

RobotMap::~RobotMap()
{

}
