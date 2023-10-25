#pragma once
#include "RenderUtils.hpp"

using namespace physx;

class Particle 
{
public:
	Particle(Vector3 Pos, Vector3 Vel);
	Particle(Vector3 Pos, Vector3 Vel, Vector3 acc, float damp, double duration, float gravity, float mass, float size);
	~Particle();
	void integrate(double t);
	bool isAlive() { return alive; };
	virtual Particle* clone() { return (new Particle(_pose.p, _vel, _acc, _damp, _duration, _gravity, _mass, _size)); }

	bool alive = true;
	double _auxDuration = 0;
	double _duration;
	float _damp;
	float _gravity;
	float _mass;
	float _size;
	Vector3 _vel;
	Vector3 _acc;
	PxTransform _pose;

protected:

	RenderItem* renderItem;
};

