#include "Gun.h"

Gun::~Gun() {
	for (int i = 0; i < balas.size(); ++i) {
		delete balas[i];
	}
}

void Gun::integrate(double t) {
	if (balas.size() > 0) {
		for (auto it = balas.begin(); it != balas.end();) {
			if ((*it)->isAlive()) {
				(*it)->integrate(t);
				++it;
			}
			else {
				//balas[i] = nullptr;
				//std::vector<Proyectil*>::iterator it = balas
				delete (*it);
				it = balas.erase(it);
			}
		}
	}
}

void Gun::shoot(pType type, Vector3 camPos, Vector3 camDir) {
	if (type == bullet) {
		vel = 45.0f;
		lifeTime = 20.0f;
		balas.push_back(new Proyectil(lifeTime, camPos, vel * camDir));
	}
	else if (type == laser) {
	
	}
	else if (type == cannonBall) {
		
	}
}