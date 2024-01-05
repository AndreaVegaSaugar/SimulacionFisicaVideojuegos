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
	Firework(FireworkGenerator* generator, int Gen, int N_hijos, Vector3 Pos, Vector3 Vel, float damp, double duration, float mass, Shape shape, Vector3 size, Vector4 color, bool isModel) : Particle(Pos, Vel, damp, duration, mass, shape, size, color, isModel), _generator(generator), _gen(Gen), _n_hijos(N_hijos) {}
	Particle* clone() override { return (new Firework(_generator, _gen, _n_hijos, _pose.p, _vel, _damp, _duration, _mass, _shape, _size, _color, false)); }
	std::list<Entity*> onDeath() override { return explode(); }
	std::list<Entity*> explode();
};

