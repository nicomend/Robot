/*
 * Graph.cpp
 *
 *  Created on: Mar 29, 2016
 *      Author: colman
 */

#include "Graph.h"

Graph::Graph(double graphResolutionInCM) {
	this->graphResolutionInCM = graphResolutionInCM;
}

Graph::~Graph() {

}

void Graph::buildGraphFromMap(RobotMap map)
{
	int graphRows = map.getHeight();
	int graphColumns = map.getWidth();
	bool isGridCellOcupied;

	this->nodes.resize(graphRows);

	for (int index = 0; index <graphRows; index++)
	{
		this->nodes[index].resize(graphColumns);
	}

	Point current;

	for (int row = 0; row < graphRows; row ++)
	{
		for (int col = 0; col < graphColumns; col ++)
		{
			current.y = row;
			current.x = col;
			isGridCellOcupied = map.checkIfInflotedMapGridCellIsOccupied(current);
			this->nodes[row][col].occupied = isGridCellOcupied;
		}
	}
}

GridCell Graph::getGridCellFromPoint(Point point)
{
	int row = point.y ;
	int col = point.x;
	GridCell gridCell(row,col);

	return gridCell;
}

void Graph::paintPathOnMap(RobotMap *map, vector<GridCell> path, int r, int g, int b)
{
	for (int pathIndex = 0; pathIndex < path.size(); pathIndex++)
	{
		paintPathOnMap(map, path[pathIndex],r,g,b);
	}
}

void Graph::paintPathOnMap(RobotMap *map, GridCell point, int r, int g, int b)
{
	Point current;

	current.y = point.row;
	current.x = point.col;
	map->paintGridCell(current,r,g,b);

}

Point Graph::getPointFromGridCell(GridCell GridCell)
{
	Point point;
	point.y = GridCell.row ;
	point.x = GridCell.col;

	return (point);
}
