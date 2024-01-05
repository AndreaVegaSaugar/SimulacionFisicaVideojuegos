#include "Firework.h"
#include "FireworkGenerator.h"

std::list<Entity*> Firework::explode() {
	auto generator = _generator->_firework_pool;
	std::list<Entity*> list;

	Particle* f;
	if (_gen < generator.size() - 1) {
		f = generator[_gen + 1];
		f->_color = _generator->color;

		
		
		ParticleGenerator* gP = new GaussianParticleGenerator("aux", Vector3(0.01, 0.01, 0.01), Vector3(9, 9, 9), _pose.p, f->_vel, _n_hijos);
		gP->setParticle(f);
		list = gP->generateParticles();
		delete gP;
	}

	return list;
}