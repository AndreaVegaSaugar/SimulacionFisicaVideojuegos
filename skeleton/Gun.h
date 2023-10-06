#pragma once
#include "Proyectil.h"
#include <vector>

using namespace physx;

enum pType{bullet, laser, cannonBall};

class Gun
{
public:
	Gun() { };
	~Gun();

	void integrate(double t);
	void shoot(pType type, Vector3 camPos, Vector3 camDir);

protected:
	std::vector<Proyectil*> balas;
	float vel;
	float lifeTime;
};
