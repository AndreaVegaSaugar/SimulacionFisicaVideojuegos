#pragma once
#include "RenderUtils.hpp"
#include <list>

using namespace physx;

class Particle 
{
public:
	Particle(Vector3 Pos, Vector3 Vel);
	Particle(Vector3 Pos, Vector3 Vel, Vector3 acc, float damp, double duration, float gravity, float mass, float size, Vector4 color);
	~Particle();
	void integrate(double t);
	bool isAlive() { return alive; };
	virtual Particle* clone() { return (new Particle(_pose.p, _vel, _acc, _damp, _duration, _gravity, _mass, _size, _color)); }
	virtual std::list<Particle*> onDeath() { std::list<Particle*> l; return l; };
	RenderItem* getRenderItem() { return renderItem; };

	bool alive = true;
	double _auxDuration = 0;
	double _duration;
	float _damp;
	float _gravity;
	float _mass;
	float _size;
	Vector4 _color;
	Vector3 _vel;
	Vector3 _acc;
	PxTransform _pose;


protected:
	RenderItem* renderItem;

};

