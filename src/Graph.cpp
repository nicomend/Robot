/*
 * Graph.cpp
 *
 *  Created on: Mar 29, 2016
 *      Author: colman
 */

#include "Graph.h"

Graph::Graph(double graphResolutionInCM) {
	this->graphResolutionInCM = graphResolutionInCM;
	this->resolutionRelation = 0;
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
	int row = point.y / resolutionRelation;
	int col = point.x / resolutionRelation;
	GridCell GridCell(row,col);
	return GridCell;
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

	for (int y = point.row * resolutionRelation; y < (point.row * resolutionRelation) + resolutionRelation; y++)
	{
		for (int x = point.col * resolutionRelation; x < (point.col * resolutionRelation) + resolutionRelation; x++)
		{
			current.y = y;
			current.x = x;
			map->paintGridCell(current,r,g,b);
		}
	}
}

Point Graph::getPointFromGridCell(GridCell GridCell)
{
	Point point;
	point.y = (GridCell.row * resolutionRelation) + (resolutionRelation / 2);
	point.x = (GridCell.col * resolutionRelation) + (resolutionRelation / 2);

	return (point);
}
