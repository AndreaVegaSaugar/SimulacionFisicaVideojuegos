#include "UniformSolidRigidGenerator.h"

UniformSolidRigidGenerator::~UniformSolidRigidGenerator() {
	delete pos_x; delete pos_y; delete pos_z;
	delete vel_x; delete vel_y; delete vel_z;
}

list<SolidRigid*> UniformSolidRigidGenerator::generateSolidRigids() {
	list<SolidRigid*> solidRigids;
	if (!checkLimit()) {
		for (int i = 0; i < _n_solidRigids; ++i) {
			SolidRigid* p = _model->clone();
			p->_pose.p.x = (*pos_x)(_mt);
			p->_pose.p.y = (*pos_y)(_mt);
			p->_pose.p.z = (*pos_z)(_mt);
			p->_rD->setGlobalPose({ (*pos_x)(_mt), (*pos_y)(_mt), (*pos_z)(_mt) });

			p->_vel.x = (*vel_x)(_mt);
			p->_vel.y = (*vel_y)(_mt);
			p->_vel.z = (*vel_z)(_mt);
			p->_rD->setLinearVelocity({ (*vel_x)(_mt), (*vel_y)(_mt), (*vel_z)(_mt) });

			solidRigids.push_back(p);
		}
	}
	return solidRigids;
}