/*
 * Main.cpp
 *
 *  Created on: April 16, 2016
 *      Author: Eylam Milner 311212419
 *      		Lucas Aides	 324392992
 */

#include "Map.h"
#include "Graph.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include "AStarAlgorithm.h"
#include "ConfigurationManager.h"
#include "Cell.h"
#include "WaypointManager.h"
#include "Lucatron.h"

using namespace std;

int main()
{
	ConfigurationManager configMgr("parameters.txt");

	// Creating a map object with the given parameters
	Map map(configMgr.mapResolutionCM, configMgr.robotHeight, configMgr.robotWidth);

	// Loading map
	map.loadMap(configMgr.mapFile);

	// Inflate all of the obstacles in the give map
	map.inflateObstacles();

	// Create a graph from map to run the a star algorithm on it
	Graph graph(configMgr.gridResolutionCM);
	graph.buildGraphFromMap(map);

	Cell start = graph.getCellFromPoint(configMgr.robotStart);
	Cell goal = graph.getCellFromPoint(configMgr.goal);
	AStarAlgorithm algo(graph.nodes, start, goal);
	vector<Cell> path = algo.StartAlgorithm();
	graph.paintPathOnMap(&map, path,255,0,0);

	// Create a waypoint instance
	WaypointManager wpMgr(algo.StartAlgorithm(), configMgr.gridResolutionCM, configMgr.mapResolutionCM);

	Position startPosition(configMgr.robotStart.x, configMgr.robotStart.y, configMgr.robotStartYAW);
	LocalizationManager* localizationManager = new LocalizationManager(&startPosition, &map);
	Lucatron lucatron("localhost", 6665, &configMgr, graph.nodes.size(), &wpMgr, &map, localizationManager);

	//Lucatron lucatron("10.10.245.63", 6665, &configMgr, graph.nodes.size(), &wpMgr, &map);

	Waypoint wayPoint;

	lucatron.setYaw(wpMgr.waypoints[0].yaw);

	for (int i = 1; i < wpMgr.waypoints.size(); i++)
	{
		wayPoint = wpMgr.waypoints[i];
		wpMgr.setNextWaypoint(wayPoint);
		lucatron.goToWaypoint(wpMgr.waypoints[i-1].yaw);

		if (i < wpMgr.waypoints.size() -1)
			lucatron.setYaw(wayPoint.yaw);
	}

	// Return value
	return 0;
}
