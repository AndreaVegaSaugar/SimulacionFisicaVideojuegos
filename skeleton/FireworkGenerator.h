#pragma once
#include "Firework.h"

static const Vector3 _gravity = { 0, -10.0, 0 };

class FireworkGenerator
{
protected:
	Vector3 pos, vel;
	int n_FireworkGens = 5;

public:
	std::vector<Firework*> _firework_pool;

	FireworkGenerator();
	Particle* shoot();
	//std::vector<Firework*> getPool() { return _firework_pool; };
};

