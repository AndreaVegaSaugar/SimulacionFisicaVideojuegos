#include "Proyectil.h"

Proyectil::~Proyectil() {
	renderItem->release();
}

void Proyectil::integrate(double t) {
	if (alive) {
		lifeSpent += t;
		alive = lifeSpent < lifeTime;

		//pose.p += (vel * pow(damp, t)) * t + 0.5 * acc * pow(t, 2);
		pose.p += vel * t;
		// Update linear velocity
		vel += acc * t;
		// Impose drag (damping)
		vel *= powf(damp, t);
	}
}