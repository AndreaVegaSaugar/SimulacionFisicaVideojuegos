#include "ParticleDragGenerator.h"

void ParticleDragGenerator::updateForce(Particle* particle, double t) {
	//Check that the particle has finite mass
	if (fabs(1/particle->_mass) < 1e-10) //ponia _inv_mass
		return;
	if (isInZone(particle, _zone)) {
		Vector3 v = particle->_vel;
		//Vector3 aux = _wind - v;
		Vector3 dragF;
		dragF = _k1 * (_wind - v) + _k2 * (_wind - v).magnitude() * (_wind - v);

		particle->addForce(dragF);
	}
}