#pragma once
#include "Particle.h"
#include "SolidRigid.h"
#include <vector>
#include <list>

using namespace physx;

enum pType { RIFLE, SHOTGUN };

class Gun
{
public:
	//physx::PxScene* scene, PxPhysics* physics, Vector3 pos, Vector3 vel, double duration, float mass, Shape shape, Vector3 size, Vector4 color, bool isModel
	Gun(PxScene* scene, PxPhysics* physics, pType _type) : type(_type) { 
		weapon = new SolidRigid(scene, physics, {0, -5, -5}, {0, 0, 0}, -1, 1, CUBE, {1, 1, 5}, {0.1, 0.1, 0.1, 1}, false);
	};

	~Gun();

	Entity* shoot(Vector3 dir, Vector3 pos);
	void integrate(double t);
	inline void changeGun(pType newType) {
		type = newType;
	}

protected:
	bool isTurningUp = false;
	bool isTurningDown = false;
	float turningTime = 0.1f;
	float auxTimer = 0;
	pType type;
	//solido rigido con forma de el cañon del arma
	SolidRigid* weapon;
};
