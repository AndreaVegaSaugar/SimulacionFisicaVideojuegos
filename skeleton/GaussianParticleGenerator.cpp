#include "GaussianParticleGenerator.h"

GaussianParticleGenerator::~GaussianParticleGenerator() {
	delete pos_x; delete pos_y; delete pos_z;
	delete vel_x; delete vel_y; delete vel_z;
}

list<Entity*> GaussianParticleGenerator::generateParticles() {
	list<Entity*> particles;
	for (int i = 0; i < _n_particles; ++i) {
		Particle* p = _modelP->clone();
		p->_pose.p.x = (*pos_x)(_mt);
		p->_pose.p.y = (*pos_y)(_mt);
		p->_pose.p.z = (*pos_z)(_mt);

		p->_vel.x = (*vel_x)(_mt);
		p->_vel.y = (*vel_y)(_mt);
		p->_vel.z = (*vel_z)(_mt);

		particles.push_back(p);
	}
	return particles;
}

list<Entity*> GaussianParticleGenerator::generateSolidRigids() {
	list<Entity*> solidRigids;
	for (int i = 0; i < _n_solidRigids; ++i) {
		SolidRigid* s = _modelS->clone();

		s->_rD->setGlobalPose({ (*pos_x)(_mt), (*pos_y)(_mt), (*pos_z)(_mt) });
		s->_rD->setLinearVelocity({ (*vel_x)(_mt), (*vel_y)(_mt), (*vel_z)(_mt) });

		solidRigids.push_back(s);
	}
	return solidRigids;
}