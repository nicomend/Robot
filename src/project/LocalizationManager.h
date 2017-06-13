/*
* LocalizationManager.h
*
* Created on: Jun 29, 2016
* Author: colman
*/
#ifndef LOCALIZATIONMANAGER_H_
#define LOCALIZATIONMANAGER_H_
#include "Particle.h"
#include "Map.h"
#include <vector>
#include <math.h>
#include "Position.h"
class LocalizationManager {
private:
vector<Particle> _particles;
Map* _map;
Position _storePosition;
void addParticleFromVector(const vector<Particle>& childParticles);
void createParticlesFromParticle(Particle fromParticle, bool isVectorEmpty);
public:
LocalizationManager(Position* startPosition, Map* map);
virtual ~LocalizationManager();
Particle getHighestBeliefParticle();
void updateParticles(Position* deltaPosition);
};
#endif /* LOCALIZATIONMANAGER_H_ */
