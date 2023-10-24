#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator(Vector3 gravity) {
	_model = new Particle(Vector3(0, 0, 0), Vector3(0, 30, 0), Vector3(0, 0, 0), 0.998, 20, gravity.y, 1);
}