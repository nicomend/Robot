/*
 * Lucatron.cpp
 *
 *  Created on: Jun 25, 2016
 *      Author: colman
 */

#include "Lucatron.h"

using namespace std;

Lucatron::Lucatron(char* IP, int PortNum, ConfigurationManager* Config, int gridRows, WaypointManager* wpMgr, Map* map, LocalizationManager* localizationManager)
{
	// Initialize robot's data members
	_playerClinet = new PlayerClient(IP, PortNum);
	_posProxy 	  = new Position2dProxy(_playerClinet);
	_laserProxy   = new LaserProxy(_playerClinet);
	_configMgr    = Config;
	_gridRows	  = gridRows;
	_wpMgr 		  = wpMgr;
	_map 		  = map;
	_printCount   = 0;
	_localizationManager = localizationManager;

	// Start motor
	_posProxy -> SetMotorEnable(true);

	// Setting the location data
	_posProxy->SetOdometry(((double)Config->robotStart.x / (_configMgr->gridResolutionCM / _configMgr->mapResolutionCM)/ (_configMgr->gridResolutionCM)),
						   ((_gridRows / _configMgr->gridResolutionCM) - (((double)Config->robotStart.y) / (_configMgr->gridResolutionCM / _configMgr->mapResolutionCM)/
							(_configMgr->gridResolutionCM))) ,Config->robotStartYAW*M_PI/180);
	_posProxy->SetOdometry(((double)Config->robotStart.x / (_configMgr->gridResolutionCM / _configMgr->mapResolutionCM)/ (_configMgr->gridResolutionCM)),
						   ((_gridRows / _configMgr->gridResolutionCM) - (((double)Config->robotStart.y) / (_configMgr->gridResolutionCM / _configMgr->mapResolutionCM)/
							(_configMgr->gridResolutionCM))),Config->robotStartYAW*M_PI/180);

	for (int i = 0; i < 20; i++)
		this->Read();
}

// Read the robot data
void Lucatron::Read()
{
	_printCount++;

	double lastX = _Xpos;
	double lastY = _Ypos;
	double lastYaw = _Yaw;

	// Read
	_playerClinet->Read();

	_Xpos = getXpos();
	_Ypos = getYpos();
	_Yaw = getYaw();

	double deltaRow = this->_Xpos - lastY;
	double deltaCol = this->_Ypos - lastX;
	double deltaYaw = this->_Yaw - lastYaw;

	Position delta(deltaRow, deltaCol, deltaYaw);
	_localizationManager->updateParticles(&delta);

	if (_printCount == 20)
	{
		cout << "Lucatron's Position (X,Y,Yaw): (" << _Xpos << "," << _Ypos << "," << _Yaw << ")" << endl;
		_printCount = 0;

		// paint on image
		int resolutionRelation = _configMgr->gridResolutionCM / _map->getMapResolution();
		int height = _configMgr->robotHeight;
		int width = _configMgr->robotWidth;

		Position particlePos = _localizationManager->getHighestBeliefParticle().getPosition();

		for (int i = (_Xpos * resolutionRelation) - ((width/ resolutionRelation) / 2); i <= (_Xpos * resolutionRelation) + ((width/ resolutionRelation) / 2); i++)
		{
			for (int j = (_Ypos * resolutionRelation) - ((height / resolutionRelation) / 2); j <= (_Ypos * resolutionRelation) + ((height / resolutionRelation)/ 2); j++)
			{
				if (i >=0 && i < _map->getWidth() && j >= 0 && j < _map->getHeight())
				{
					Point robot;
					robot.x = i;
					robot.y = j;

					_map->paintCell(robot,0,0,255);
				}
			}
		}

		for (int i = (particlePos.getCol() * resolutionRelation) - ((width/ resolutionRelation) / 2); i <= (particlePos.getCol() * resolutionRelation) + ((width/ resolutionRelation) / 2); i++)
		{
			for (int j = (particlePos.getRow() * resolutionRelation) - ((height / resolutionRelation) / 2); j <= (particlePos.getRow() * resolutionRelation) + ((height / resolutionRelation)/ 2); j++)
			{
				if (i >=0 && i < _map->getWidth() && j >= 0 && j < _map->getHeight())
				{
					Point robot;
					robot.x = i;
					robot.y = j;

					_map->paintCell(robot,0,255,0);
				}
			}
		}


		_map->saveMap("robotsPosition.png");

		for (int i = (_Xpos * resolutionRelation) - ((width/ resolutionRelation) / 2); i <= (_Xpos * resolutionRelation) + ((width/ resolutionRelation) / 2); i++)
				{
					for (int j = (_Ypos * resolutionRelation) - ((height / resolutionRelation) / 2); j <= (_Ypos * resolutionRelation) + ((height / resolutionRelation)/ 2); j++)
					{
				if (i >=0 && i < _map->getWidth() && j >= 0 && j < _map->getHeight())
				{
					Point robot;
					robot.x = i;
					robot.y = j;

					_map->paintCell(robot,255,255,255);
				}
			}
		}

		for (int i = (particlePos.getCol() * resolutionRelation) - ((width/ resolutionRelation) / 2); i <= (particlePos.getCol() * resolutionRelation) + ((width/ resolutionRelation) / 2); i++)
		{
			for (int j = (particlePos.getRow() * resolutionRelation) - ((height / resolutionRelation) / 2); j <= (particlePos.getRow() * resolutionRelation) + ((height / resolutionRelation)/ 2); j++)
			{
				if (i >=0 && i < _map->getWidth() && j >= 0 && j < _map->getHeight())
				{
					Point robot;
					robot.x = i;
					robot.y = j;

					_map->paintCell(robot,255,255,255);
				}
			}
		}

	}

}

// Set the moving speed
void Lucatron::setSpeed(float xSpeed, float angularSpeed)
{
	_posProxy->SetSpeed(xSpeed, angularSpeed);
}

double Lucatron::getXpos()
{
	return ((_posProxy->GetXPos()) * _configMgr->gridResolutionCM);
}

double Lucatron::getYpos()
{
	return (((_gridRows / _configMgr->gridResolutionCM) - _posProxy->GetYPos()) * _configMgr->gridResolutionCM);
}

double Lucatron::getYaw()
{
	double yaw = 180*(_posProxy->GetYaw())/M_PI;

	if(yaw >= 0)
 	{
		return (yaw);
	}

	else
	{
		return (360+yaw);
	}
}

void Lucatron::setYaw(double Yaw)
{
	double diff = _Yaw - Yaw;
	double turnSpeed = -0.1;

	if (diff < 0 || diff > 180)
	{
		turnSpeed = 0.1;
	}

	setSpeed(0,turnSpeed);

	while (abs(diff) > 2)
	{
		Read();
		diff = _Yaw - Yaw;
		turnSpeed = -0.1;

		if (diff < 0 || diff > 180)
		{
			turnSpeed = 0.1;
		}

		setSpeed(0,turnSpeed);
	}

	setSpeed(0,turnSpeed / 2);

	while (abs(diff) > 1)
	{
		Read();
		diff = _Yaw - Yaw;
		turnSpeed = -0.1;

		if (diff < 0 || diff > 180)
		{
			turnSpeed = 0.1;
		}

		setSpeed(0,turnSpeed / 2);
	}

	setSpeed(0,turnSpeed / 4);

	while (abs(diff) > 0.4)
	{
		Read();
		diff = _Yaw - Yaw;

		turnSpeed = -0.1;
		if (diff < 0 || diff > 180)
		{
			turnSpeed = 0.1;
		}

		setSpeed(0,turnSpeed / 4);
	}

	setSpeed(0,0);
}

void Lucatron::goToWaypoint(double yaw)
{
	double speed = 0.1;
	double diff;

	setSpeed(speed,0);

	while (!_wpMgr->isNearWaypoint(getXpos(), getYpos(), getYaw()))
	{
		Read();
		diff = _Yaw - yaw;
		if (abs(diff) > 1.5) { this->setYaw(yaw); }
		setSpeed(speed,0);
	}

	setSpeed(speed / 2, 0);

	while (!_wpMgr->isInWaypoint(getXpos(), getYpos(), getYaw()))
	{
		Read();
		diff = _Yaw - yaw;
		if (abs(diff) > 1.5) { this->setYaw(yaw); }
		setSpeed(speed / 2, 0);
	}

	setSpeed(0,0);
}

Lucatron::~Lucatron()
{
	delete _playerClinet;
	delete _posProxy;
	delete _laserProxy;
}

