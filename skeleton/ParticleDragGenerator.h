#pragma once
#include "ForceGenerator.h"
#include "core.hpp"
#include <iostream>

class ParticleDragGenerator : public ForceGenerator
{
public:
	ParticleDragGenerator(const float k1, const float k2, Vector3 wind = { 0, 10, 0 }) : ForceGenerator() {
		_k1 = k1; _k2 = k2; _wind = wind;
		// zona en la que se afectara a las nubes
		_zone.x_Max = 150; _zone.x_Min = -150; _zone.y_Max = 100; _zone.y_Min = 0; _zone.z_Max = 0; _zone.z_Min = -100;
	};
	virtual void updateForce(Entity* particle, double t);
	inline void setDrag(float k1, float k2) { _k1 = k1; _k2 = k2; }
	inline float getK1() { return (_k1); }
	inline float getK2() { return (_k2); }

protected:
	float _k1 = 0.0;
	float _k2 = 0.0;
	Vector3 _wind = { 0, 10, 0 };
};

