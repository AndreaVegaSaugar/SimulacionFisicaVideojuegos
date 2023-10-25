#include "FireworkGenerator.h"

FireworkGenerator::FireworkGenerator() {
	for (int i = 0; i < n_FireworkGens; ++i) {
		_firework_pool.push_back(new Firework(this, i, n_FireworkGens - (i + 1), Vector3(0, 0, 0), Vector3(0, 0 / (i + 1), 0), Vector3(0, 0, 0), 0.998, 2 / (i + 1), _gravity.y, 1, 1 / (i + 1)));
	}
}

Particle* FireworkGenerator::shoot() {
	Particle* p = _firework_pool[0]->clone();
	return p;
}