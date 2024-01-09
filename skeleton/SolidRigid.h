#pragma once
#include "Entity.h"

class SolidRigid : public Entity
{
public:


	physx::PxScene* _scene = NULL;
	physx::PxPhysics* _physics = NULL;
	PxRigidDynamic* _rD = nullptr;
	PxRigidStatic* _rS = nullptr;

	SolidRigid(physx::PxScene* scene, PxPhysics* physics, Vector3 pos, Vector3 vel, double duration, float mass, Shape shape, Vector3 size, Vector4 color, bool isModel);
	SolidRigid(physx::PxScene* scene, physx::PxPhysics* physics, Vector3 pos, Shape shape, Vector3 size, Vector4 color);
	virtual ~SolidRigid();
	void integrate(double t);

	inline virtual SolidRigid* clone() {
		return (new SolidRigid(_scene, _physics, _pose.p, _vel, _duration, _mass, _shape, _size, _color, false));
	}

	inline void addForce(Vector3 f) {
		if(_rD != nullptr && alive)_rD->addForce(f);	
	}
};

