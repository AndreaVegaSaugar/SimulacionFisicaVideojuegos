#include "GravityForceGenerator.h"

void GravityForceGenerator::updateForce(Entity* p, double t) {
	//Check that the particle has Finite Mass
	if (fabs(1/p->_mass ) < 1e-10) //ponia _inv_mass
		return;

	//Apply the mass scaled gravity
	p->addForce(_gravity * p->_mass);
}