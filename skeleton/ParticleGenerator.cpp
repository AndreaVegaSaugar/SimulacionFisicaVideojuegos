#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator(PxScene* scene, PxPhysics* physics) {
	if(scene != nullptr) _modelS = new SolidRigid(scene, physics, Vector3(0, 0, 0), Vector3(0, 30, 0), 10, 1, SPHERE, Vector3(3, 3, 3), Vector4(255, 255, 0, 1), true);
	else _modelP = new Particle(Vector3(0, 0, 0), Vector3(0, 30, 0), 0.998, 20, 1, SPHERE, Vector3(1, 1, 1), Vector4 (255, 255, 0, 1), true);
}