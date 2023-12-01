#pragma once
#include "ForceGenerator.h"
#include <math.h>

class BuoyancyForceGenerator : public ForceGenerator
{
public:
	BuoyancyForceGenerator(float h, float d, Vector3 dim) : _height(h), _liquid_density(d), _dim(dim), ForceGenerator() {
		//float mass = d * v;
		_liquid_particle = new Particle({ 0, 0, 0 }, { 0 ,0 ,0 }, { 0, 0, 0 }, 0, 1000, 0, dim, { 0, 0, 255, 0 }, false);

	};
	void updateForce(Particle* particle, double t);
	inline void changeMass(double k) { _liquid_density += k; };
	virtual ~BuoyancyForceGenerator();

protected:
	Vector3 _dim;
	float _height;
	float _liquid_density;
	float _gravity = 10;
	Particle* _liquid_particle;
};

