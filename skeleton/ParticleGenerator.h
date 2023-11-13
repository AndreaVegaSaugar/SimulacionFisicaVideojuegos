#pragma once
#include <list>
#include <string>
#include "Particle.h"
#include <time.h>
#include <random>

using namespace std;

class ParticleGenerator {

protected:
	string _name;

	Particle* _model = nullptr; 
	int _n_particles = 1; 
	std::random_device rd{};
	std::mt19937 _mt{ rd() };

public:
	ParticleGenerator();
	~ParticleGenerator();
	string getName() { return _name; }
	void setParticle(Particle* model) { 
		if (_model != nullptr) delete _model;
		_model = model; 
	};
	inline void setNParticles(int n_p) { _n_particles = n_p; }
	virtual list<Particle*> generateParticles() = 0;
};

