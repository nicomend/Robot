#include <HamsterAPIClientCPP/Hamster.h>
#include <iostream>
using namespace std;
using namespace HamsterAPI;

int main() {
	try {
		Hamster* hamster = new HamsterAPI::Hamster(1);

		cv::namedWindow("OccupancyGrid-view");
		while (hamster->isConnected()) {
			try {

				int robotRadiusInCM = 20;

				OccupancyGrid ogrid = hamster->getSLAMMap();

				int resulation = ogrid.getResolution() * 100;
				int pixels = robotRadiusInCM / resulation;
				int width = ogrid.getWidth();
				int height = ogrid.getHeight();
				unsigned char pixel;
				cv::Mat m = cv::Mat(width, height, CV_8UC1);

				// Build the pixel mat
				for (int i = 0; i < height; i++)
					for (int j = 0; j < width; j++) {
						if (ogrid.getCell(i, j) == CELL_FREE)
							pixel = 255;
						else if (ogrid.getCell(i, j) == CELL_OCCUPIED) {
							pixel = 0;
						} else
							pixel = 128;
						m.at<unsigned char>(i, j) = pixel;

						if (pixel == 0) {
							for (int x = i - pixels; x < i + pixels; x++) {
								for (int y = j - pixels; y < j + pixels; y++) {
									m.at<unsigned char>(x, y) = pixel;
								}
							}
						}
					}

				// Show the pixel mat
				cv::imshow("OccupancyGrid-view", m);
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
