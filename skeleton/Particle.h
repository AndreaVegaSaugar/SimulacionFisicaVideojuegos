#pragma once
#include "RenderUtils.hpp"
#include <list>
#include "Entity.h"

class Particle : public Entity
{
public:

	Particle(Vector3 Pos, Vector3 Vel, float damp, double duration, float mass, Shape shape, Vector3 size, Vector4 color, bool isModel);
	~Particle();
	void integrate(double t);
	inline virtual Particle* clone() { return (new Particle(_pose.p, _vel, _damp, _duration, _mass, _shape, _size, _color, false)); }
	
	// Add force to apply in next integration only
	inline void addForce(Vector3 f) {
		_force += f;
	}
	// Clears accumulated force
	inline void clearForce() {
		_force *= 0.0;
	}

	// Accumulated force
	
	float _damp;

protected:
	RenderItem* renderItem;

};

