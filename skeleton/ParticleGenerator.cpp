#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator() {
	_model = new Particle(Vector3(0, 0, 0), Vector3(0, 30, 0), Vector3(0, 0, 0), 0.998, 20, 1, 1.0f, Vector4 (255, 255, 0, 1), true);
}

ParticleGenerator::~ParticleGenerator() {
	//delete _model;
}