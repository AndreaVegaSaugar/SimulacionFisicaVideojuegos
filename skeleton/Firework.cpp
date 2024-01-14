#include "Firework.h"
#include "FireworkGenerator.h"

std::list<Entity*> Firework::explode() {
	auto generator = _generator->_firework_pool;
	std::list<Entity*> list;

	Particle* f;
	if (_gen < generator.size() - 1) {
		f = generator[_gen + 1];
		f->_vel = { float(rand() % 31) - 15, float(rand() % 31) - 15, float(rand() % 31) - 15 };
		f->_color = { float(rand() % 256 / 255.0f), float(rand() % 256 / 255.0f), float(rand() % 256 / 255.0f), 1 };
		
		ParticleGenerator* gP = new GaussianParticleGenerator("firework", Vector3(0.01, 0.01, 0.01), Vector3(9, 9, 9), _pose.p, f->_vel, _n_hijos);
		gP->setParticle(f);
		list = gP->generateParticles();
		delete gP;
	}

	return list;
}