#pragma once
#include "Particle.h"
/*
						***** Por defecto es una bala de 45 mm ******
vel real = 450m/s, vel sim = 45m/s, masa real = 0.01 kg, masa sim = 1kg, grv real = 9.8m/s^2, grv sim = -0.098m/s^2
*/

class Proyectil
{
public:
	Proyectil(float LifeTime, Vector3 Pos, Vector3 Vel = { 0, 45.0f, 0 }, Vector3 Acc = { 0, -0.098f, 0 }, float Mass = 1.0f, float Gravity = -0.098f, float Damp = 0.998) {
		lifeTime = LifeTime;
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
	~Proyectil();

	void integrate(double t);
	bool isAlive() { return alive; };

private:
	bool alive = true;
	float lifeSpent = 0;
	float lifeTime;
	int mass;
	float damp;
	Vector3 vel;
	PxTransform pose;
	Vector3 acc;
	RenderItem* renderItem;
};

