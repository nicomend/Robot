/*
 * AStarAlgorithm.cpp
 */

#include "AStarAlgorithm.h"
using namespace std;
AStarAlgorithm::AStarAlgorithm(vector<vector<Node> > graph, GridCell start, GridCell goal) {
	this->graph = graph;
	this->goal = goal;
	this->start = start;
}

void AStarAlgorithm::fillHeuristic()
{
	int k = graph.size();
	int m = graph[0].size();

	for (unsigned int row = 0; row < graph.size(); row++)
	{
		for(unsigned int col = 0; col < graph[row].size(); col++)
		{
			if (!graph[row][col].occupied)
			{
				GridCell current(row,col);
				graph[row][col].hValue = estimatedHeuristicCost(current,goal);
				graph[row][col].gValue = INT_MAX;
				graph[row][col].fValue = INT_MAX;
			}
		}
	}
}

vector<GridCell> AStarAlgorithm::StartAlgorithm()
{
	fillHeuristic();
	closedSet.clear();
	openSet.clear();
	graph[start.row][start.col].gValue = 0;
	graph[start.row][start.col].fValue = graph[start.row][start.col].hValue;

	openSet.insert(start);

	while (!openSet.empty())
	{
		GridCell current = getLowestFValue();
		if (current == goal)
		{
			reconstructPath();
			return totalPath;
		}

		openSet.erase(current);
		closedSet.insert(current);

		for(int row = current.row -1; row <= current.row + 1; row++)
		{
			for(int col = current.col -1; col <= current.col + 1; col++)
			{
				if (row >= 0 && row < graph.size() &&
					col >= 0 && col < graph[0].size() && !graph[row][col].occupied)
				{
					GridCell neighbour(row,col);

					if (setContains(closedSet, neighbour))
					{
						continue;
					}

					int tentativeGValue = graph[current.row][current.col].gValue + getGValue(current, neighbour);

					if (setContains(openSet, neighbour) || tentativeGValue >= graph[neighbour.row][neighbour.col].gValue)
					{
						continue;
					}

					graph[neighbour.row][neighbour.col].parrent = current;
					graph[neighbour.row][neighbour.col].gValue = tentativeGValue;
					graph[neighbour.row][neighbour.col].fValue = tentativeGValue + graph[neighbour.row][neighbour.col].hValue;

					if (!setContains(openSet, neighbour))
					{
						openSet.insert(neighbour);
					}
				}
			}
		}
	}

	return totalPath;
}

bool AStarAlgorithm::setContains(set<GridCell> nodeSet, GridCell current)
{
	if (!nodeSet.empty())
	{
		for (set<GridCell>::iterator index = nodeSet.begin(); index != nodeSet.end(); index++)
		{
			if (*index == current)
			{
				return true;
			}
		}
	}

	return false;
}

double AStarAlgorithm::getGValue(GridCell from, GridCell to)
{
	if((from.col != to.col) && ( from.row != to.row))
	{
		return (14);
	}
	else
	{
		return (10);
	}
}

GridCell AStarAlgorithm::getLowestFValue()
{
	set<GridCell>::iterator index = openSet.begin();
	GridCell lowest = *index;
	GridCell current;

	for (index = openSet.begin(); index != openSet.end(); index++)
	{
		current = *index;

		if (graph[current.row][current.col].fValue < graph[lowest.row][lowest.col].fValue)
		{
			lowest = current;
		}
	}

	return lowest;
}

double AStarAlgorithm::estimatedHeuristicCost(GridCell from, GridCell to)
{
	int dx = from.col - to.col;
	int dy = from.row - to.row;

	double dist = pow(dx,2) + pow(dy,2);

	return sqrt(dist);
}

void AStarAlgorithm::reconstructPath()
{
	int i = 1;

	GridCell current = goal;
	while (current != start)
	{
		i++;
		current = graph[current.row][current.col].parrent;
	}

	totalPath.resize(i);

	current = goal;
	totalPath[i - 1] = current;

	for (i = i - 2; i >= 0; i--)
	{
		totalPath[i] = current;
		current = graph[current.row][current.col].parrent;
	}
}

AStarAlgorithm::~AStarAlgorithm() {
	// TODO Auto-generated destructor stub
}

