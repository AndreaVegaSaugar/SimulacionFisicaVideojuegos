#include "Particle.h"

Particle::Particle(Vector3 pos, Vector3 vel, float damp, double duration, float mass, Shape shape, Vector3 size, Vector4 color, bool isModel):Entity() {
	_vel = vel;
	_pose = PxTransform(pos);
	_damp = damp;
	_duration = duration;
	_mass = mass;
	_shape = shape;
	_size = size;
	_color = color;
	_isModel = isModel;

	PxShape* auxShape;

	if (_shape == SPHERE) {
		PxSphereGeometry sphere(size.x);
		auxShape = CreateShape(sphere);
	}
	else  {
		PxBoxGeometry square(size);
		auxShape = CreateShape(square);
	}

	if (!_isModel) renderItem = new RenderItem(auxShape, &_pose, _color);
}

Particle::~Particle() {
	if(renderItem != nullptr) renderItem->release();
}

void Particle::integrate(double t) {

	if (alive) {

		if (_duration != -1) {
			_auxDuration += t;
			alive = _auxDuration < _duration;
		}

		// Get the accel considering the force accum
		Vector3 resulting_accel = _force * (1/_mass);
		_vel += resulting_accel * t; // Ex. 1.3 --> add acceleration
		_vel *= powf(_damp, t); // Exercise 1.3 --> add damping
		_pose.p += _vel * t;
		clearForce();
	}
}