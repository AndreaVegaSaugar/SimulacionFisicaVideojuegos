#pragma once
#include "ForceGenerator.h"

class SpringForceGenerator : public ForceGenerator 
{
public:
	SpringForceGenerator(double k, double resting_length, Entity* other);
	virtual void updateForce(Entity* particle, double t);
	inline void setK(double k) { _k = k; }
	inline void addK(double k) { _k += k; };
	virtual ~SpringForceGenerator();

protected:
	double _k;
	double _resting_length;
	Entity* _other;

};

