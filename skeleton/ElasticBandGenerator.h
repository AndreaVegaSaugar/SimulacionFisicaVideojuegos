#pragma once
#include "SpringForceGenerator.h"

class ElasticBandGenerator : public SpringForceGenerator
{
public:
	ElasticBandGenerator(double k, double resting_length, Particle* other);
	void updateForce(Particle* p, double t);
	inline void addK(double k) { _k += k; };
};

