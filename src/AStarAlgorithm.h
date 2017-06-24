/*
 * AStarAlgorithm.h
 *
 *  Created on: May 27, 2016
 *      Author: colman
 */

#ifndef ASTARALGORITHM_H_
#define ASTARALGORITHM_H_

#include "set"
#include "vector"
#include "Graph.h"
#include "math.h"
#include "GridCell.h"

class AStarAlgorithm {

private:
	vector<vector<Node> > graph;
	GridCell start;
	GridCell goal;
	set<GridCell> openSet;
	set<GridCell> closedSet;
	vector<GridCell> totalPath;

public:
	AStarAlgorithm(vector<vector<Node> > graph, GridCell start, GridCell goal);
	virtual ~AStarAlgorithm();
	vector<GridCell> StartAlgorithm();
	double getGValue(GridCell from, GridCell to);
	bool setContains(set<GridCell> nodeSet, GridCell current);
	GridCell getLowestFValue();
	double estimatedHeuristicCost(GridCell from, GridCell to);
	void reconstructPath();
	void fillHeuristic();
	void fillGAndFValues(GridCell from);
};

#endif /* ASTARALGORITHM_H_ */
