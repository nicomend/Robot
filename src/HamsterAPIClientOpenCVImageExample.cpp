#include <HamsterAPIClientCPP/Hamster.h>
#include <iostream>
using namespace std;
using namespace HamsterAPI;

int main() {

	try {
		Hamster* hamster = new HamsterAPI::Hamster(1);
		Map robotMap = new Map(20);
		cv::namedWindow("OccupancyGrid-view");

		if (hamster->isConnected()) {
			try {

				cv::Mat matrix = robotMap.inflateMap(hamster);
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
