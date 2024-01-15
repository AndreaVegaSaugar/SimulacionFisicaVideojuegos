#pragma once
#include "Particle.h"
#include "SolidRigid.h"
#include <vector>
#include <list>
#include <random>

using namespace physx;

enum pType { RIFLE = 0, SHOTGUN = 1};

// clase que se encarga de el arma y sus proyectiles
class Gun
{
public:
	Gun(PxScene* scene, PxPhysics* physics, pType _type) : type(_type) { 
		weapon = new SolidRigid(scene, physics, {0, -5, -5}, {0, 0, 0}, -1, 1, CUBE, {1, 1, 5}, {0.1, 0.1, 0.1, 1}, false);
		deviation = std::uniform_real_distribution<float>(0.0f, 0.07f);
		srand(time(NULL));
	};

	virtual ~Gun();

	std::list<Entity*> shoot(Vector3 dir, Vector3 pos);
	void integrate(double t);
	inline void changeWeapon() {
		if (type == RIFLE) type = SHOTGUN;
		else type = RIFLE;
	}
	inline pType getActiveWeapon() {
		return type;
	}

private:
	//solido rigido que actua como el cañon del arma y se mueve cada vez que disparamos
	SolidRigid* weapon = nullptr;
	bool isTurningUp = false;
	bool isTurningDown = false;
	float turningTime = 0.1f;
	float auxTimer = 0;
	int balasShotgun = 5;
	Vector3 auxDir;
	pType type;
	std::random_device rd{};
	std::mt19937 _mt{ rd() };
	std::uniform_real_distribution<float> deviation;

};
