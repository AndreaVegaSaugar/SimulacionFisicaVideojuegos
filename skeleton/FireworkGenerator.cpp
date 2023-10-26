#include "FireworkGenerator.h"

FireworkGenerator::FireworkGenerator() {

	_firework_pool.push_back(new Firework(this, 0, 10, Vector3(0, 0, 0), Vector3(0, 40.0f, 0), Vector3(0, 0, 0), 0.998, 1.f, _gravity.y, 1.0f, 1.0f, Vector4(255, 255, 0, 1)));
	_firework_pool.push_back(new Firework(this, 1, 7, Vector3(0, 0, 0), Vector3(15, 15, 15), Vector3(0, 0, 0), 0.998, 0.3f, _gravity.y, 1.0f, 0.6f, Vector4(255, 255, 0, 1)));
	_firework_pool.push_back(new Firework(this, 2, 4, Vector3(0, 0, 0), Vector3(10, 10, 10), Vector3(0, 0, 0), 0.998, 0.3f, _gravity.y, 1.0f, 0.5f, Vector4(255, 255, 0, 1)));
	_firework_pool.push_back(new Firework(this, 3, 2, Vector3(0, 0, 0), Vector3(8, 8, 8), Vector3(0, 0, 0), 0.998, 0.3f, _gravity.y, 1.0f, 0.4f, Vector4(255, 255, 0, 1)));
	_firework_pool.push_back(new Firework(this, 4, 0, Vector3(0, 0, 0), Vector3(5, 5, 5), Vector3(0, 0, 0), 0.998, 3.0f, _gravity.y, 1.0f, 0.3f, Vector4(255, 255, 0, 1)));
	
	n_FireworkGens = _firework_pool.size();
}

Particle* FireworkGenerator::shoot() {
	srand(time(NULL));
	color = Vector4(float(rand() % 256 / 255.0f), float(rand() % 256 / 255.0f), float(rand() % 256 / 255.0f), 1);

	Particle* p = _firework_pool[0]->clone();
	p->getRenderItem()->setColor(color);
	return p;
}