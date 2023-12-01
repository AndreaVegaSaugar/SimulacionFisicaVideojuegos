#include "AnchoredSpring.h"

AnchoredSpring::AnchoredSpring(double k, double resting, const Vector3& anchor_pos) : SpringForceGenerator(k, resting, nullptr) {
	_other = new Particle(anchor_pos, { 0, 0, 0 }, { 0, 0, 0 }, 0.998, 1000, 1, {1, 1, 1}, {255, 255, 0, 1}, false);
}

AnchoredSpring::~AnchoredSpring() {
	delete _other;
}