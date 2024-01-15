#include "Gun.h"

Gun::~Gun() {
	delete(weapon);
}

// metodo que se encarga de instanciar los proyectiles, en caso de tener equipado el rifle sera solo uno, con mayor masa y escala
// y en el caso de la escopeta seran cinco, con menor masa y escala ademas de menor precision 
std::list<Entity*> Gun::shoot(Vector3 dir, Vector3 pos) {
	std::list<Entity*> balas;
	isTurningUp = true;
	weapon->_rD->setAngularVelocity({ 1, 0, 0 });

	if (type == RIFLE) {
		balas.push_back(new Particle(pos, dir * 300, 0.998f, 10, 1.0f, SPHERE, {0.2f, 0.2f, 0.2f}, {10, 0, 0, 1}, false));
	}
	else if (type == SHOTGUN) {
		for (int i = 0; i < balasShotgun; ++i) {
			auxDir = dir;
			auxDir.x += (deviation(_mt) * ((rand() % 3) - 1) ); auxDir.y += (deviation(_mt) * ((rand() % 3) - 1));
			balas.push_back(new Particle(pos, auxDir * 300, 0.998f, 10, 0.5f, SPHERE, { 0.1f, 0.1f, 0.1f }, { 10, 0, 0, 1 }, false));
		}
	}
	return balas;
}

void Gun::integrate(double t) {

	if (isTurningUp) {

		auxTimer += t;

		if (auxTimer >= turningTime) {

			isTurningUp = false;
			auxTimer = 0;
			weapon->_rD->setAngularVelocity({ -1, 0, 0 });
			isTurningDown = true;
		}
	}
	else if (isTurningDown) {

		auxTimer += t;

		if (auxTimer >= turningTime) {

			isTurningDown = false;
			auxTimer = 0;
			weapon->_rD->setAngularVelocity({ 0, 0, 0 });
		}
	}
}