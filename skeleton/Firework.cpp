#include "Firework.h"
#include "FireworkGenerator.h"

std::list<Particle*> Firework::explode() {
	auto generator = _generator->_firework_pool;
	std::list<Particle*> list;

	Particle* f = generator[_gen + 1]->clone();
	GaussianParticleGenerator* gP = new GaussianParticleGenerator("aux", Vector3(0.01, 0.01, 0.01), Vector3(10, 5, 10), _pose.p, f->_vel, Vector3(0, -10.0, 0), _n_hijos);
	list = gP->generateParticles();

	for (auto it = list.begin(); it != list.end(); ++it) {
		static_cast<Firework*>(*it)->_gen++;
		static_cast<Firework*>(*it)->_n_hijos--;
	}

	return list;
}