#include "Gun.h"

Gun::~Gun() {
	delete weapon;
}

Entity* Gun::shoot(int x, int y) {
	Entity* bala;
	if (type == RIFLE) {
		//bala = new Particle()
	}
	else if (type == SHOTGUN) {
		
	}
	return bala;
}