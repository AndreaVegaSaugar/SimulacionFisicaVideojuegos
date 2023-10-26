#include "GaussianParticleGenerator.h"

GaussianParticleGenerator::~GaussianParticleGenerator() {
	delete pos_x; delete pos_y; delete pos_z;
	delete vel_x; delete vel_y; delete vel_z;
}

list<Particle*> GaussianParticleGenerator::generateParticles() {
	list<Particle*> particles;
	for (int i = 0; i < _n_particles; ++i) {
		Particle* p = _model->clone();
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