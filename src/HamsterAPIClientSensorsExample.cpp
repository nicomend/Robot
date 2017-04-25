///*
// * HamsterAPISensorsExample.cpp
// *
// *  Created on: Jul 21, 2016
// *      Author: ofir
// */
//
//#include <HamsterAPIClientCPP/Hamster.h>
//
//int main(int argc, char ** argv)
//{
//	try
//	{
//		HamsterAPI::Hamster hamster(1);
//
//		while(hamster.isConnected())
//		{
//			try
//			{
//				HamsterAPI::GPS gps = hamster.getGPS();
//				HamsterAPI::IMU imu = hamster.getIMU();
//				HamsterAPI::LidarScan lidar = hamster.getLidarScan();
//				HamsterAPI::Pose pose = hamster.getPose();
//				HamsterAPI::Image image = hamster.getCameraImage();
//
//				HamsterAPI::Log::i("Client",gps.toString());
//				HamsterAPI::Log::i("Client",imu.toString());
//				HamsterAPI::Log::i("Client",lidar.toString());
//				HamsterAPI::Log::i("Client",pose.toString());
//				HamsterAPI::Log::i("Client",image.toString());
//			}
//			catch(const HamsterAPI::HamsterError & message_error)
//			{
//				HamsterAPI::Log::i("Client",message_error.what());
//			}
//		}
//	}
//	catch(const HamsterAPI::HamsterError & connection_error)
//	{
//		HamsterAPI::Log::i("Client",connection_error.what());
//	}
//}
//
//
//
