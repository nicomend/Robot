#include <HamsterAPIClientCPP/Hamster.h>
#include <iostream>
#include "RobotMap.h"
#include "Graph.h"
#include <fstream>
#include <string>
#include <sstream>
#include "AStarAlgorithm.h"
#include "GridCell.h"
#include "WaypointManager.h"
using namespace std;
using namespace HamsterAPI;

int main() {

	try {
		Hamster* hamster = new HamsterAPI::Hamster(1);
		int robotSizeCM = 20;
		RobotMap robotMap(robotSizeCM);
		cv::namedWindow("OccupancyGrid-view");

		if (hamster->isConnected()) {
			try {

				cv::Mat matrix = robotMap.inflateMap(hamster);
				// Calculate  way points by a start algo
				// Create a graph from map to run the a star algorithm on it
				Graph graph(robotMap.getResulotion());
				graph.buildGraphFromMap(robotMap);

				GridCell startGridCell(0,0);
				GridCell goalGridCell(5,2);
				AStarAlgorithm algo(graph.nodes, startGridCell, goalGridCell);
				vector<GridCell> path = algo.StartAlgorithm();
				graph.paintPathOnMap(&robotMap, path,255,0,0);

				// iterate through way points
				for (int i=0; i<5; i++) {

				}

				// Show the pixel mat
				cv::imshow("OccupancyGrid-view", matrix);
				cv::waitKey(1);

			} catch (const HamsterAPI::HamsterError & message_error) {
				HamsterAPI::Log::i("Client", message_error.what());
			}

		}
	} catch (const HamsterAPI::HamsterError & connection_error) {
		HamsterAPI::Log::i("Client", connection_error.what());
	}
	return 0;

}
