#include "WhirlwindGenerator.h"

void WhirlwindGenerator::updateForce(Entity* particle, double t) {
	if (fabs(1/particle->_mass) < 1e-10)//ponia _inv_mass
		return;
	if (isInZone(particle, _zone)) {
		//Compute the Drag force
		Vector3 p = particle->_pose.p;

		_wind = _K * Vector3(-(p.z - _center.z) * 5, (p.y - _center.y) * 2, (p.x - _center.x) * 5);

		ParticleDragGenerator::updateForce(particle, t);
	}
}