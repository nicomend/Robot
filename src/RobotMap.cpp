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

// Paints a cell on the map
void RobotMap::paintGridCell(Point point, int r, int g, int b)
{
	// Set the inflated GridCell color
	this->matrix.at<cv::Vec3b>(point.y, point.x)[0] = r;
	this->matrix.at<cv::Vec3b>(point.y, point.x)[1] = g;
	this->matrix.at<cv::Vec3b>(point.y, point.x)[2] = b;
}

// Checking if a specific GridCell of the infloted map is occupied
bool RobotMap::checkIfInflotedMapGridCellIsOccupied(Point point) const
{
	return ((this->infaltedMatrix.at<cv::Vec3b>(point.y, point.x)[0]==0) &&
			(this->infaltedMatrix.at<cv::Vec3b>(point.y, point.x)[1]==0) && (this->infaltedMatrix.at<cv::Vec3b>(point.y, point.x)[2]==0));
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
	cv::Vec3b pixel;
	this->matrix = cv::Mat(width, height, CV_8UC3);
	this->infaltedMatrix = cv::Mat(width, height, CV_8UC3);

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
			infaltedMatrix.at<cv::Vec3b>(i, j) = pixel;
			matrix.at<cv::Vec3b>(i,j) = pixel;

			if (ogrid.getCell(i, j) == CELL_OCCUPIED) {
				for (int x = i - pixels; x < i + pixels; x++) {
					for (int y = j - pixels; y < j + pixels; y++) {
						infaltedMatrix.at<cv::Vec3b>(x, y)[0] = 0;
						infaltedMatrix.at<cv::Vec3b>(x, y)[1] = 0;
						infaltedMatrix.at<cv::Vec3b>(x, y)[2] = 0;
					}
				}
			}
		}

	return matrix;
}

RobotMap::~RobotMap()
{

}
