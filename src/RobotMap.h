/*
 * RobotMap.h
 */
#include <HamsterAPIClientCPP/Hamster.h>

#ifndef ROBOTMAP_H_
#define ROBOTMAP_H_

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
class RobotMap {
private:
	cv::Mat matrix;
	int robotSize;
	unsigned int mapHeight;
	unsigned int mapWidth;
	int resulotion;

public:
	RobotMap(int robotSize);
	int getResulotion();
	cv::Mat inflateMap(Hamster* hamster);
	unsigned int getWidth() const;
	unsigned int getHeight() const;
	bool checkIfInflotedMapGridCellIsOccupied(Point point) const;
	void paintGridCell(Point point, int r, int g, int b);
	bool checkIfGridCellIsOccupied(Point point);
	virtual ~RobotMap();
};

#endif /* ROBOTMAP_H_ */
