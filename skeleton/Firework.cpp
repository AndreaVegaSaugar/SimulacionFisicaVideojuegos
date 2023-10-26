#include "Firework.h"
#include "FireworkGenerator.h"

std::list<Particle*> Firework::explode() {
	auto generator = _generator->_firework_pool;
	std::list<Particle*> list;

	Particle* f;
	if (_gen < generator.size() - 1) {
		f = generator[_gen + 1];
		f->_color = _generator->color;

		GaussianParticleGenerator* gP = new GaussianParticleGenerator("aux", Vector3(0.01, 0.01, 0.01), Vector3(9, 9, 9), _pose.p, f->_vel, Vector3(0, -10.0, 0), _n_hijos);
		gP->setParticle(f);
		list = gP->generateParticles();
		delete gP;
	}

	return list;
}