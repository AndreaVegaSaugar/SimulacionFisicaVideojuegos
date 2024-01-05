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
	Gun(PxScene* scene, PxPhysics* physics, pType _type) : type(_type) { 
	
		//weapon = new SolidRigid(scene, physics, pos, CUBE, size, {10, 10, 10, 1});
	};

	~Gun();

	Entity* shoot( int x, int y);
	inline void changeGun(pType newType) {
		type = newType;
	}

protected:
	pType type;
	SolidRigid* weapon;
	//solido rigido con forma de el cañon del arma
};
