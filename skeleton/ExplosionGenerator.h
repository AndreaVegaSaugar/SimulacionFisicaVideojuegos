#pragma once
#define _USE_MATH_DEFINES
#include "ForceGenerator.h"
#include <cmath>


class ExplosionGenerator : public ForceGenerator
{
public:
	ExplosionGenerator(Vector3 center, int lifeTime, const float K, const float R, const float T) : ForceGenerator() {
		_K = K; _radius = R; _T = T;
		_center = center;
		_duration = lifeTime;
	}
	void updateForce(Entity* particle, double t);
	inline void setAlive(bool alive) { _alive = alive; }

protected:
	float _K, _radius, _T;
};

