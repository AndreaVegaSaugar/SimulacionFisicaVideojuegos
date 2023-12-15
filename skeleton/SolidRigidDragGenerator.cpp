#include "SolidRigidDragGenerator.h"

void SolidRigidDragGenerator::updateForce(SolidRigid* soliRigid, double t) {
	//Check that the particle has finite mass
	if (fabs(1 / soliRigid->_mass) < 1e-10) //ponia _inv_mass
		return;
	if (isInZone(soliRigid, _zone)) {
		Vector3 v = soliRigid->_vel;
		//Vector3 aux = _wind - v;
		Vector3 dragF;
		dragF = _k1 * (_wind - v) + _k2 * (_wind - v).magnitude() * (_wind - v);

		soliRigid->addForce(dragF);
	}
}