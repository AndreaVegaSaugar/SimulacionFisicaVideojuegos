#pragma once
#include "Firework.h"
#include<stdlib.h>
#include <time.h>

static const Vector3 _gravity = { 0, -10.0, 0 };

class FireworkGenerator
{
protected:
	Vector3 pos, vel;

public:
	std::vector<Firework*> _firework_pool;
	Vector4 color;

	FireworkGenerator();
	~FireworkGenerator();
	Particle* shoot();
};

