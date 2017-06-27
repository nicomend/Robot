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
		int robotSizeCM = 20;

	try {
		RobotMap robotMap(robotSizeCM);
		cv::namedWindow("OccupancyGrid-view");

		Hamster* hamster = new HamsterAPI::Hamster(1);
		sleep(3);
		cv::Mat matrix = robotMap.inflateMap(hamster);
		// Calculate  way points by a start algo
		// Create a graph from map to run the a star algorithm on it
		Graph graph(robotMap.getResulotion());
		graph.buildGraphFromMap(robotMap);

		GridCell startGridCell(470,470);
		GridCell goalGridCell(443, 613);
		AStarAlgorithm algo(graph.nodes, startGridCell, goalGridCell);
		vector<GridCell> path = algo.StartAlgorithm();
		graph.paintPathOnMap(&robotMap, path,255,0,0);

		while (hamster->isConnected()) {
			try {
				// iterate through way points
//				for (int i=0; i<5; i++) {
//
//				}

				// Show the pixel mat
				cv::imshow("OccupancyGrid-view", matrix);
				cv::waitKey(1);
				sleep(0.2);

			} catch (const HamsterAPI::HamsterError & message_error) {
				HamsterAPI::Log::i("Client", message_error.what());
			}

		}
	} catch (const HamsterAPI::HamsterError & connection_error) {
		HamsterAPI::Log::i("Client", connection_error.what());
	}
	return 0;

}
