#pragma once
#include "RenderUtils.hpp"
#include <list>

using namespace physx;

struct Zone {
	float x_Max, x_Min;
	float y_Max, y_Min;
	float z_Max, z_Min;
};

class Particle 
{
public:
	Particle(Vector3 Pos, Vector3 Vel);
	Particle(Vector3 Pos, Vector3 Vel, Vector3 acc, float damp, double duration, float mass, float size, Vector4 color, bool isModel);
	~Particle();
	void integrate(double t);
	inline bool isAlive() { return alive; };
	inline virtual Particle* clone() { return (new Particle(_pose.p, _vel, _acc, _damp, _duration, _mass, _size, _color, false)); }
	virtual std::list<Particle*> onDeath() { std::list<Particle*> l; return l; };
	inline RenderItem* getRenderItem() { return renderItem; };
	// Add force to apply in next integration only
	inline void addForce(Vector3 f) {
		_force += f;
	}
	// Clears accumulated force
	inline void clearForce() {
		_force *= 0.0;
	}

	// Accumulated force
	Vector3 _force = {0 , 0 , 0};
	bool _isModel = false;
	bool alive = true;
	double _auxDuration = 0;
	double _duration;
	float _damp;
	float _mass;
	float _size;
	Vector4 _color;
	Vector3 _vel;
	Vector3 _acc;
	PxTransform _pose;


protected:
	RenderItem* renderItem;

};

