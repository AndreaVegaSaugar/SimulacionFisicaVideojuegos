#include "WhirlwindSolidRigidGenerator.h"

void WhirlwindSolidRigidGenerator::updateForce(SolidRigid* solidRigid, double t) {
	if (fabs(1 / solidRigid->_mass) < 1e-10)//ponia _inv_mass
		return;
	std::cout << "aaaaaaaaa" << std::endl;
	if (isInZone(solidRigid, _zone)) {
		//Compute the Drag force
		Vector3 p = solidRigid->_pose.p;

		_wind = _K * Vector3(-(p.z - _center.z) * 5, (p.y - _center.y) * 5, (p.x - _center.x) * 5);

		SolidRigidDragGenerator::updateForce(solidRigid, t);
	}
}