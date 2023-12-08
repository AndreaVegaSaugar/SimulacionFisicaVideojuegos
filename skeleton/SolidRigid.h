#pragma once
#include "RenderUtils.hpp"
#include <iostream>
#include <list>

using namespace physx;

struct Zone2 {
	float x_Max, x_Min;
	float y_Max, y_Min;
	float z_Max, z_Min;
};

class SolidRigid
{
protected:
	RenderItem* renderItem;
public:
	PxScene* _scene;
	PxPhysics* _physics;
	PxRigidDynamic* _rD;
	PxTransform _pose;
	Vector3 _vel;
	double _duration;
	float _mass;
	float _size;
	Vector4 _color;
	bool _isModel;

	bool alive = true;
	double auxDuration = 0;

	SolidRigid(PxScene* scene, PxPhysics* physics, Vector3 Pos, Vector3 Vel, double duration, float mass, float size, Vector4 color, bool isModel);
	~SolidRigid();
	void integrate(double t);
	inline bool isAlive() { return alive; };

	inline virtual SolidRigid* clone() {
		return (new SolidRigid(_scene, _physics, _pose.p, _vel, _duration, _mass, _size, _color, false));
	}

	inline void addForce(Vector3 f) {
		if(_rD != nullptr && alive)_rD->addForce(f);	
	}
};

