#include "SolidRigidGenerator.h"

SolidRigidGenerator::SolidRigidGenerator(PxScene* scene, PxPhysics* physics) {
	_model = new SolidRigid(scene, physics, Vector3(0, 50, 0), Vector3(0, 0, 0), 100, 1, CUBE, Vector3(5, 5, 5), Vector4(255, 255, 0, 1), true);
}

SolidRigidGenerator::~SolidRigidGenerator() {
	//delete _model;
}