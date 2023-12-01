#pragma once
#include "ForceGenerator.h"

class SpringForceGenerator : public ForceGenerator 
{
public:
	SpringForceGenerator(double k, double resting_length, Particle* other);
	virtual void updateForce(Particle* particle, double t);
	inline void setK(double k) { _k = k; }
	inline void addK(double k) { _k += k; };
	virtual ~SpringForceGenerator();

protected:
	double _k;
	double _resting_length;
	Particle* _other;

};

