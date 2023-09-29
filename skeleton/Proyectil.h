#pragma once
#include "Particle.h"

/*
vel real = 450m/s, vel sim = 45m/s, masa real = 0.01 kg, masa sim = 1kg, grv real = 9.8m/s^2, grv sim = -0.098m/s^2
*/

class Proyectil : public Particle
{
public:
	Proyectil(Vector3 Pos, Vector3 Vel = { 0, 45.0f, 0 }, Vector3 Acc = { 0, -0.098f, 0 }, float Mass = 1.0f, float Gravity = -0.098f, float Damp = 0.998) : Particle(Pos, Vel) {
		//mover las movidas del cpp aqui
	}
	~Proyectil();

	void integrate(double t);

private:
	int mass;
	float damp;
	Vector3 vel;
	Vector3 acc;
	PxTransform pose;
	RenderItem* renderItem;
};

