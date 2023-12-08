#pragma once
#include <cmath>
#include "SolidRigidForceGenerator.h"

class ExplosionSolidRigidGenerator : public SolidRigidForceGenerator
{
public:
	ExplosionSolidRigidGenerator(Vector3 center, int lifeTime, const float K, const float R, const float T) : SolidRigidForceGenerator() {
		_K = K; _radius = R; _T = T;
		_center = center;
		_duration = lifeTime;
	}
	void updateForce(SolidRigid* sR, double t);
	inline void setAlive(bool alive) { _alive = alive; }


protected:
	float _K, _radius, _T;
};

