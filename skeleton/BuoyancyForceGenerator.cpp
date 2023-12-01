#include "BuoyancyForceGenerator.h"

void BuoyancyForceGenerator::updateForce(Particle* particle, double t) {
	float h = particle->_pose.p.y;
	float h0 = _liquid_particle->_pose.p.y;

	Vector3 f(0, 0, 0);
	float inmersed = 0.0;
	if (h - h0 > _height * 0.5) {
		inmersed = 0.0;
	}
	else if (h0 - h > _height * 0.5) {
		inmersed = 1.0;
	}
	else {
		inmersed = (h0 - h) / _height + 0.5;
	}
	f.y = _liquid_density * (particle->getVolume()) * inmersed * _gravity;

	particle->addForce(f);
}

BuoyancyForceGenerator::~BuoyancyForceGenerator() {
	delete _liquid_particle;
}