/*
 * Graph.h
 *
 *  Created on: Mar 29, 2016
 *      Author: colman
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include "RobotMap.h"
#include "set"
#include "GridCell.h"

typedef struct node
{
	bool occupied;
	double fValue;
	double gValue;
	double hValue;
	GridCell parrent;
}
Node;

class Graph {
private:
	double	graphResolutionInCM;
	double	resolutionRelation;
public:
	vector<vector<Node> > nodes;
	void buildGraphFromMap(RobotMap map);
	Graph(double graphResolutionInCM);
	virtual ~Graph();
	GridCell getGridCellFromPoint(Point point);
	Point getPointFromGridCell(GridCell GridCell);
	void paintPathOnMap(RobotMap *map, vector<GridCell> path, int r, int g, int b);
	void paintPathOnMap(RobotMap *map, GridCell GridCell, int r, int g, int b);
};

#endif /* GRAPH_H_ */
