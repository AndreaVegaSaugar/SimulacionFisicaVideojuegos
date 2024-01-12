#pragma once
#include <list>
#include <string>
#include "Particle.h"
#include "SolidRigid.h"
#include <time.h>
#include <random>

using namespace std;

class ParticleGenerator {

protected:
	string _name;
	Particle* _modelP = nullptr;
	SolidRigid* _modelS = nullptr;
	int _n_particles = 1; 
	int _n_solidRigids = 1;
	std::random_device rd{};
	std::mt19937 _mt{ rd() };

public:
	double generationTime = 1;
	double auxTime = 0;

	ParticleGenerator(PxScene* scene = nullptr, PxPhysics* physics = nullptr);
	string getName() { return _name; }
	void setParticle(Particle* modelP) {
		if (_modelP != nullptr) delete _modelP;
		_modelP = modelP; 
	};
	inline void setNParticles(int n_p) { _n_particles = n_p; }
	inline void setNSolidRigids(int n_s) { _n_solidRigids = n_s; }
	virtual list<Entity*> generateParticles() = 0;
	virtual list<Entity*> generateSolidRigids() = 0;
};

