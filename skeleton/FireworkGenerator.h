#pragma once
#include "Firework.h"
#include<stdlib.h>
#include <time.h>

class FireworkGenerator
{
protected:
	Vector3 pos, vel;

public:
	std::vector<Firework*> _firework_pool;
	FireworkGenerator();
	~FireworkGenerator();
	Entity* shoot(Vector3 pos);
};

