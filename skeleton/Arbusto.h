#pragma once
#include <vector>
#include <random>
#include "SolidRigid.h"

class Arbusto
{
	SolidRigid* base;
	std::vector<SolidRigid*> frutos;
	std::uniform_real_distribution<float> deviationX;
	std::uniform_real_distribution<float> deviationY;
	std::random_device rd{};
	std::mt19937 _mt{ rd() };

public:
	Arbusto(PxScene* scene, PxPhysics* physics, Vector3 pos, Vector3 size, Vector4 colorFrutos) {
		base = new SolidRigid(scene, physics, pos, CUBE, size, { 0.1, 0.7, 0.1, 1 });

		deviationX = std::uniform_real_distribution<float>(pos.x - size.x, pos.x + size.x);
		deviationY = std::uniform_real_distribution<float>(pos.y - size.y, pos.y + size.y);

		for (int i = 0; i < 10; ++i) {
			frutos.push_back(new SolidRigid(scene, physics, { deviationX(_mt), deviationY(_mt), pos.z + size.z}, CUBE, {0.5, 0.5, 0.5}, colorFrutos));
		}
	}

	~Arbusto() {
		delete base;
		for (SolidRigid* s : frutos) {
			delete s;
		}
	}
};

