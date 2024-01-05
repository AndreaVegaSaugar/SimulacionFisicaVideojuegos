#pragma once
#include "SpringForceGenerator.h"

class ElasticBandGenerator : public SpringForceGenerator
{
public:
	ElasticBandGenerator(double k, double resting_length, Entity* other);
	void updateForce(Entity* p, double t);
	inline void addK(double k) { _k += k; };
};

