#include "Proyectil.h"

Proyectil::Proyectil(Vector3 Pos, Vector3 Vel, Vector3 Acc, float Mass, float Gravity, float Damp) {
	vel = Vel;
	acc = Acc;
	damp = Damp;
	mass = Mass;
	pose = PxTransform(Pos);
	PxSphereGeometry sphere(1);
	PxShape* shape = CreateShape(sphere);
	Vector4 color = { 255, 255, 0, 1 };
	renderItem = new RenderItem(shape, &pose, color);
}

Proyectil::~Proyectil() {
	renderItem->release();
}

void Particle::integrate(double t) {
	//pose.p += (vel * pow(damp, t)) * t + 0.5 * acc * pow(t, 2);
	pose.p += vel * t;
	// Update linear velocity
	vel += acc * t;
	// Impose drag (damping)
	vel *= powf(damp, t);
}