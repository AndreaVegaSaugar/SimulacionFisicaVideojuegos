#include "FireworkGenerator.h"

FireworkGenerator::FireworkGenerator() {
	srand(time(NULL));

	_firework_pool.push_back(new Firework(this, 0, 5, { 0, 0, 0 }, { 0, 0, 0 }, 0.998, 0.1f, 1.0f, SPHERE, Vector3(0.7f), {255.0f, 255.0f, 0.0f, 1 }, true));
	_firework_pool.push_back(new Firework(this, 1, 4, { 0, 0, 0 }, {0, 0, 0}, 0.998, 0.1f, 0.8f, SPHERE, Vector3(0.6f), { 255.0f, 255.0f, 0.0f, 1 }, true));
	_firework_pool.push_back(new Firework(this, 2, 3, { 0, 0, 0 }, { 0, 0, 0 }, 0.998, 0.15f, 0.6f, SPHERE, Vector3(0.5f), { 255.0f, 255.0f, 0.0f, 1 }, true));
	_firework_pool.push_back(new Firework(this, 3, 2, { 0, 0, 0 }, { 0, 0, 0 }, 0.998, 0.15f, 0.4f, SPHERE, Vector3(0.4f), { 255.0f, 255.0f, 0.0f, 1 }, true));
	_firework_pool.push_back(new Firework(this, 4, 0, { 0, 0, 0 }, { 0, 0, 0 }, 0.998, 0.2, 0.2f, SPHERE, Vector3(0.3f), { 255.0f, 255.0f, 0.0f, 1 }, true));
}

FireworkGenerator::~FireworkGenerator() {
	for (int i = 0; i < _firework_pool.size(); i++) {
		delete _firework_pool[i];
	}
}

Entity* FireworkGenerator::shoot(Vector3 pos) {
	Entity* p = _firework_pool[0]->clone();
	p->_pose.p = pos;
	return p;
}