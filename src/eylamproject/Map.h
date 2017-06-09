/*
 * Map.h
 *
 *  Created on: April 16, 2016
 *      Author: Eylam Milner 311212419
 *      		Lucas Aids	 324392992
 */

#ifndef MAP_H_
#define MAP_H_

#include <vector>
#include <string>

using namespace std;

typedef struct point
{
	double x;
	double y;
}
Point;

class Map {
private:
	unsigned int width;
	unsigned int height;
	vector<vector<bool> > map;
	vector<vector<bool> > inflotedMap;
	vector<unsigned char> pixels;
	vector<unsigned char> inflotedPixels;
	double mapResolution;
	double robotHeight;
	double robotWidth;

	void setInflotedCellIsOccupied(Point point);
	void printMap() const;
	void printInflotedMap() const;

public:
	Map(double mapResolution, double robotHeight, double robotWidth);
	void loadMap(const string mapFile);
	void saveMap(const string mapFile);
	void inflateObstacles();
	virtual ~Map();
	unsigned int getWidth() const;
	unsigned int getHeight() const;
	double getMapResolution() const;
	bool checkIfInflotedMapCellIsOccupied(Point point) const;
	void paintCell(Point point, int r, int g, int b);
	bool checkIfCellIsOccupied(Point point);
};

#endif /* MAP_H_ */
