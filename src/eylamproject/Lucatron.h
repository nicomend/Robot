/*
 * Lucatron.h
 *
 *  Created on: Jun 25, 2016
 *      Author: colman
 */

#ifndef LUCATRON_H_
#define LUCATRON_H_


#include <libplayerc++/playerc++.h>
#include "ConfigurationManager.h"
#include "WaypointManager.h"
#include "Map.h"
#include "LocalizationManager.h"

using namespace PlayerCc;

class Lucatron {
	PlayerClient* _playerClinet;
	Position2dProxy* _posProxy;
	LaserProxy* _laserProxy;
	SonarProxy* _sonarProxy;
	ConfigurationManager* _configMgr;
	WaypointManager* _wpMgr;
	Map* _map;
	int _printCount ;
	LocalizationManager* _localizationManager;

	public:
	//Robot constructor & destructor
	Lucatron(char* IP, int PortNum, ConfigurationManager* Config, int gridRows, WaypointManager* wpMgr, Map* map, LocalizationManager* localizationMgr);
	virtual ~Lucatron();

	// Robot position
	double _Xpos;
	double _Ypos;
	double _Yaw;
	int    _gridRows;

	// Get the robot position
	double getXpos();
	double getYpos();
	double getYaw();

	// Set the robot position
	void setXpos(double Xpos);
	void setYpos(double Ypos);
	void setYaw(double  Yaw);

	void setSpeed(float xSpeed, float angularSpeed);
	void goToWaypoint(double yaw);
	void Read();
};

#endif /* LUCATRON_H_ */
