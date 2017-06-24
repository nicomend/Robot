/*
 * WaypointManager.h
 *
 *  Created on: Jun 4, 2016
 *      Author: colman
 */

#ifndef WAYPOINTMANAGER_H_
#define WAYPOINTMANAGER_H_
#include "Map.h"
#include <set>
#include "Graph.h"
#include "math.h"
#include "Waypoint.h"
#include "GridCell.h"

using namespace std;
#include <iostream>


class WaypointManager {
public:
	vector<Waypoint> waypoints;
	Waypoint currWaypoint;

	WaypointManager(vector<GridCell> path, double gridResolution, double mapResolution);
	void buildWaypointVector(int numberOfGridCells);
	void setNextWaypoint(Waypoint Next);
	bool isInWaypoint(double x,double y, double yaw);
	bool isNearWaypoint(double x,double y, double yaw);
	virtual ~WaypointManager();

private:
	vector<GridCell> astarPath;
	bool isVerticle = 0;
	Waypoint nextWaypoint;
	double gridResolution;
	double mapResolution;

	double calculateYaw(double m, GridCell from, GridCell to);
	double calculateIncline(GridCell from, GridCell to);
};

#endif /* WAYPOINTMANAGER_H_ */
