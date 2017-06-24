/*
 * Map.h
 *
 *  Created on: April 16, 2016
 *      Author: Eylam Milner 311212419
 *      		Lucas Aids	 324392992
 */
#include <HamsterAPIClientCPP/Hamster.h>

#ifndef MAP_H_
#define MAP_H_

#include <vector>
#include <string>

using namespace std;
using namespace HamsterAPI;
typedef struct point
{
	double x;
	double y;
}
Point;

class Map {
private:
	int robotSize;

public:
	Map(int robotSize);
	cv::Mat inflateMap(Hamster* hamster);
	virtual ~Map();
	void paintCell(Point point, int r, int g, int b);
};

#endif /* MAP_H_ */
