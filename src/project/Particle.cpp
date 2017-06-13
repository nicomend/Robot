/*
* Particle.cpp
*
* Created on: Jun 29, 2016
* Author: colman
*/
#include "Particle.h"
Particle::Particle(double row, double col, double yaw, float belief, Map* map)
{
	this->_position = Position(row, col, yaw);
	this->_belief = belief;
	this->_map = map;
}

Particle::Particle(Position pos, float belief, Map* map)
{
	this->_position = pos;
	this->_belief = belief;
	this->_map = map;
	this->_position = createPositionRandomly(pos);

	Point positionPoint;
	positionPoint.x = _position.getCol();
	positionPoint.y = _position.getRow();

	// run until we get particle not on block
	while (this->_map->checkIfCellIsOccupied(positionPoint))
	{
		this->_position = createPositionRandomly(pos);
		positionPoint.x = _position.getCol();
		positionPoint.y = _position.getRow();
	}
}

Position Particle::getPosition()
{
	return this->_position;
}

double Particle::getRow()
{
	return _position.getRow();
}

double Particle::getCol()
{
	return _position.getCol();
}

double Particle::getYaw()
{
	return _position.getYaw();
}

float Particle::getBelief()
{
	return this->_belief;
}

Position Particle::createPositionRandomly(Position currentPosition)
{
	if (currentPosition.getCol() < 0 || currentPosition.getCol() >= _map->getWidth())
		currentPosition.setCol(0);
	if (currentPosition.getRow() < 0 || currentPosition.getRow() >= _map->getHeight())
			currentPosition.setRow(0);

	// Calc range of delta particle
	int rowRange = floor(_map->getHeight() / 2 * 0.3);
	int colRange = floor(_map->getWidth() / 2 * 0.3);
	double YawRange = M_PI * 2 / 2 * 0.1;
	int intYawRange = YawRange * 10000;

	int deltaRow = (rand() % (2 * rowRange)) - rowRange;
	int deltaCol = (rand() % (2 * colRange)) - colRange;
	double deltaYaw = (rand() % (2 * intYawRange)) - intYawRange;
	deltaYaw = deltaYaw / 10000;

	Position randomLocation = Position(currentPosition.getRow() + deltaRow,
	currentPosition.getCol() + deltaCol,
	currentPosition.getYaw() + deltaYaw);
	return randomLocation;
}

Particle Particle::createParticle()
{
	// Generate particle (the constructor of particle(position) creates random particle
	return Particle(_position, _belief * 0.9, _map);
}

float Particle::UpdateParticle(double dRow, double dCol, double dYaw)
{
	this->_position.setRow(this->_position.getRow() + dRow);
	this->_position.setCol(this->_position.getCol() + dCol);
	this->_position.setYaw(this->_position.getYaw() + dYaw);
	this->_belief = 1.1 * ProbByMove(dRow, dCol, dYaw) * this->_belief; // ProbByLaser(laserArray) *

	if (this->_belief > 1)
	{
		this->_belief = 1;
	}

	return this->_belief;
}
float Particle::ProbByMove(double dRow, double dCol, double dYaw)
{
	float distance = sqrt(pow(dCol, 2) + pow(dRow, 2));

	// Check if the robot moved really really little bit
	if (distance < 0.2 && abs(dYaw) < 0.1)
	{
		return 0.9;
	}
	if (distance < 0.4 && abs(dYaw) < 0.2)
	{
		return 0.7;
	}
	if (distance < 0.7 && abs(dYaw) < 0.3)
	{
		return 0.4;
	}

	return 0.3;
}

Particle::~Particle() {
// TODO Auto-generated destructor stub
}
