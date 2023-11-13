#include "Particle.h"

Particle::Particle(Vector3 Pos, Vector3 Vel) {
	_vel = Vel;
	_pose = PxTransform(Pos);

	PxSphereGeometry sphere(1);
	PxShape* shape = CreateShape(sphere);
	Vector4 color = { 255, 255, 0, 1 };
	renderItem = new RenderItem(shape, &_pose, color);
}

Particle::Particle(Vector3 pos, Vector3 vel, Vector3 acc, float damp, double duration, float mass, float size, Vector4 color, bool isModel) {
	_vel = vel;
	_pose = PxTransform(pos);
	_acc = acc;
	_damp = damp;
	_duration = duration;
	_mass = mass;
	_size = size;
	_color = color;
	_isModel = isModel;

	PxSphereGeometry sphere(_size);
	PxShape* shape = CreateShape(sphere);
	if(!_isModel) renderItem = new RenderItem(shape, &_pose, _color);
}

Particle::~Particle() {
	if(!_isModel) renderItem->release();
}

void Particle::integrate(double t) {
	//pose.p += vel * t;
	if (alive) {

		//_pose.p += _vel * t;
		//// Update linear velocity
		//_vel += /*_acc*/Vector3(0, _gravity, 0) * t;
		//// Impose drag (damping)
		//_vel *= powf(_damp, t);

		_auxDuration += t;
		alive = _auxDuration < _duration;
		// Get the accel considering the force accum
		Vector3 resulting_accel = _force * _mass;
		_vel += resulting_accel * t; // Ex. 1.3 --> add acceleration
		_vel *= powf(_damp, t); // Exercise 1.3 --> add damping
		_pose.p += _vel * t;
		clearForce();
	}
}