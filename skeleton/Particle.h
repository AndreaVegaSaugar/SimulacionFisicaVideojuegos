#pragma once
#include "RenderUtils.hpp"

using namespace physx;

class Particle 
{
public:
	Particle(Vector3 Pos, Vector3 Vel);
	~Particle();

	void integrate(double t);

protected:
	Vector3 vel;
	PxTransform pose;
	RenderItem* renderItem;
};

