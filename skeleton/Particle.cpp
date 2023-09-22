#include "Particle.h"

Particle::Particle(Vector3 Pos, Vector3 Vel) {
	vel = Vel;
	pose = PxTransform(Pos);

	PxSphereGeometry sphere(1);
	PxShape* shape = CreateShape(sphere);
	Vector4 color = { 255, 255, 0, 1 };
	renderItem = new RenderItem(shape, &pose, color);
}

Particle::~Particle() {
	renderItem->release();
}

void Particle::integrate(double t) {
	pose.p += vel * t;
}