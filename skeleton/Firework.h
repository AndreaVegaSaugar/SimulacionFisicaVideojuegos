#pragma once
#include "GaussianParticleGenerator.h"
#include <list>

class FireworkGenerator;
class Firework : public Particle
{
protected:
	int _gen;
	int _n_hijos;
	FireworkGenerator* _generator = nullptr;

public:
	Firework(FireworkGenerator* generator, int Gen, int N_hijos, Vector3 Pos, Vector3 Vel, Vector3 acc, float damp, double duration, float gravity, float mass, float size) : Particle(Pos, Vel, acc, damp, duration, gravity, mass, size), _generator(generator), _gen(Gen), _n_hijos(N_hijos) {

	}
	Particle* clone() override { return (new Firework(_generator, _gen, _n_hijos, _pose.p, _vel, _acc, _damp, _duration, _gravity, _mass, _size)); }
	std::list<Particle*> explode();
};

