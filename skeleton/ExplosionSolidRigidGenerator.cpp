#include "ExplosionSolidRigidGenerator.h"

void ExplosionSolidRigidGenerator::updateForce(SolidRigid* sR, double t) {
	if (_alive) {
		if (fabs(1 / sR->_mass) < 1e-10)
			return;

		Vector3 p = sR->_pose.p;
		Vector3 dist = p - _center;

		if (dist.magnitude() < _radius) {
			//Compute the Drag force

			Vector3 explosionForce = (_K / (powf(dist.magnitude(), 2)) * dist * (exp(-_t / _T)));

			sR->addForce(explosionForce);
		}
	}
};