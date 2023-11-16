#include "ExplosionGenerator.h"


void ExplosionGenerator::updateForce(Particle* particle, double t) {
	if (fabs(1 / particle->_mass) < 1e-10)
		return;

	Vector3 p = particle->_pose.p;
	Vector3 dist = p - _center;

	if (dist.magnitude() < _radius) {
		//Compute the Drag force

		Vector3 explosionForce = (_K / (powf(dist.magnitude(), 2)) * dist * (exp(-_t / _T)));

		particle->addForce(explosionForce);
	}
};