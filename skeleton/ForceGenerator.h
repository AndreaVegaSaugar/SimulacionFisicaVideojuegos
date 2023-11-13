#pragma once
#include "Particle.h"

class ForceGenerator {
protected:
	ForceGenerator() {};
public:
	std::string _name;
	virtual void updateForce(Particle* particle, double t) = 0;
	double _t = 0.0; // If starting negative --> eternal
	double _duration = -1e10;
	inline bool updateTime(double t) {
		_t += t;
		return _t < _duration || _duration < 0.0; // Devuelve true si ya era cero o si es positivo
	}
	virtual ~ForceGenerator() {}
};
