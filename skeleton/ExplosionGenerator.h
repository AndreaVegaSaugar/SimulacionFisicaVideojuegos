#pragma once
#define _USE_MATH_DEFINES
#include "ForceGenerator.h"
#include <cmath>


class ExplosionGenerator : public ForceGenerator
{
public:
	ExplosionGenerator(const float K, const float R, const float T) : ForceGenerator() {
		_K = K; _radius = R; _T = T;
		//_zone.x_Max = 200; _zone.x_Min = -200; _zone.y_Max = 200; _zone.y_Min = 0; _zone.z_Max = 200; _zone.z_Min = -200;
		//pensar mas lo del centro y los valores abs
		_center = Vector3(0, 10, 0);
	}
	void updateForce(Particle* particle, double t);

protected:
	float _K, _radius, _T;
};

