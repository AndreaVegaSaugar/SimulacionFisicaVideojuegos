#include "Gun.h"

Gun::~Gun() {
	delete weapon;
}

Entity* Gun::shoot(Vector3 dir, Vector3 pos) {
	Entity* bala;
	isTurningUp = true;
	weapon->_rD->setAngularVelocity({ 1, 0, 0 });
	//std::cout << x << " " << y << std::endl;

	if (type == RIFLE) {
		bala = new Particle({0 ,0 ,0}, dir * 200, 0.998f, 10, 1.0f, SPHERE, {0.2f, 0.2f, 0.2f}, {10, 0, 0, 1}, false);
	}
	else if (type == SHOTGUN) {
		
	}
	return bala;
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