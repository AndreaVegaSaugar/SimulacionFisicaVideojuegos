#pragma once
#include "GaussianParticleGenerator.h"
#include <list>

class FireworkGenerator;
class Firework : public Particle
{
protected:
	int _gen = 0;
	int _n_hijos = 0;
	FireworkGenerator* _generator = nullptr;

public:
	Firework(FireworkGenerator* generator, int Gen, int N_hijos, Vector3 Pos, Vector3 Vel, Vector3 acc, float damp, double duration, float mass, float size, Vector4 color, bool isModel) : Particle(Pos, Vel, acc, damp, duration, mass, size, color, isModel), _generator(generator), _gen(Gen), _n_hijos(N_hijos) {}
	Particle* clone() override { return (new Firework(_generator, _gen, _n_hijos, _pose.p, _vel, _acc, _damp, _duration, _mass, 1.0, _color, false)); }
	std::list<Particle*> onDeath() override { return explode(); }
	std::list<Particle*> explode();
};

