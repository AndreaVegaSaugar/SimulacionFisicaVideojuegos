#pragma once
#include "SolidRigid.h"
#include <list>
#include <string>
#include "Particle.h"
#include <time.h>
#include <random>

using namespace std;

class SolidRigidGenerator {

protected:
	string _name;
	const int _max_solidRigids = 50;
	int _solidRigids_Generated = 0;
	SolidRigid* _model = nullptr;
	int _n_solidRigids = 1;
	std::random_device rd{};
	std::mt19937 _mt{ rd() };

public:
	double generationTime = 1.5;
	double auxTime = 0;

	SolidRigidGenerator(PxScene* scene, PxPhysics* physics);
	~SolidRigidGenerator();
	string getName() { return _name; }
	void setSolidRigid(SolidRigid* model) {
		if (_model != nullptr) delete _model;
		_model = model;
	};
	inline bool checkLimit() {
		_solidRigids_Generated++;
		return (_solidRigids_Generated >= _max_solidRigids);
	}
	inline void setNSolidRigids(int n_p) { _n_solidRigids = n_p; }
	virtual list<SolidRigid*> generateSolidRigids() = 0;
};


