#include "FireworkGenerator.h"

FireworkGenerator::FireworkGenerator() {

	_firework_pool.push_back(new Firework(this, 0, 10, Vector3(0, 0, 0), Vector3(0, 40.0f, 0), 0.998, 1.f, 1.0f, SPHERE, Vector3(1.0f), Vector4(255, 255, 0, 1), true));
	_firework_pool.push_back(new Firework(this, 1, 7, Vector3(0, 0, 0), Vector3(15, 15, 15), 0.998, 0.3f, 1.0f, SPHERE, Vector3(0.6f), Vector4(255, 255, 0, 1), true));
	_firework_pool.push_back(new Firework(this, 2, 4, Vector3(0, 0, 0), Vector3(10, 10, 10), 0.998, 0.3f, 1.0f, SPHERE, Vector3(0.5f), Vector4(255, 255, 0, 1), true));
	_firework_pool.push_back(new Firework(this, 3, 2, Vector3(0, 0, 0), Vector3(8, 8, 8), 0.998, 0.3f, 1.0f, SPHERE, Vector3(0.4f), Vector4(255, 255, 0, 1), true));
	_firework_pool.push_back(new Firework(this, 4, 0, Vector3(0, 0, 0), Vector3(5, 5, 5), 0.998, 3.0f, 1.0f, SPHERE, Vector3(0.3f), Vector4(255, 255, 0, 1), true));
}

FireworkGenerator::~FireworkGenerator() {
	for (int i = 0; i < _firework_pool.size(); i++) {
		delete _firework_pool[i];
	}
}

Entity* FireworkGenerator::shoot() {
	color = Vector4(float(rand() % 256 / 255.0f), float(rand() % 256 / 255.0f), float(rand() % 256 / 255.0f), 1);

	Entity* p = _firework_pool[0]->clone();
	p->getRenderItem()->setColor(color);
	return p;
}