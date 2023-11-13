#include "ParticleDragGenerator.h"

void ParticleDragGenerator::updateForce(Particle* particle, double t) {
	//Check that the particle has finite mass
	if (fabs(particle->_mass) < 1e-10) //ponia _inv_mass
		return;

	//Compute the Drag force
	Vector3 v = particle->_vel;
	float drag_coef = v.normalize();
	Vector3 dragF;
	drag_coef = _k1 * drag_coef + _k2 * drag_coef * drag_coef;
	dragF = -v * drag_coef;
	//Apply the drag force
	std::cout << dragF.x << "\t" << dragF.y << "\t" << dragF.z << std::endl;
	particle->addForce(dragF);
}