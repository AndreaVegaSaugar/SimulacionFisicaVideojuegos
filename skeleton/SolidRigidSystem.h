#pragma once
#include <list>
#include "GaussianSolidRigidGenerator.h"
#include "UniformSolidRigidGenerator.h"
#include "SolidRigidForceRegistry.h"
#include "ExplosionSolidRigidGenerator.h"
#include "WhirlwindSolidRigidGenerator.h"
#include <iostream>

using namespace std;

class SolidRigidSystem
{
protected:
	list<SolidRigid*> _solidRigids;
	list<SolidRigidGenerator*> _solidRigid_generators;
	list<SolidRigidForceGenerator*> _solidRigid_force_generators;
	list<ExplosionSolidRigidGenerator*> _explosion_solidRigid_generators;
	SolidRigidForceRegistry* _solidRigid_force_registry;
	Zone _zone;
	PxScene* scene;

public:
	SolidRigidSystem(PxScene* scene, PxPhysics* physics);
	~SolidRigidSystem();
	void update(double t);
	void generateExplosion();
	void generateTornado();

	bool isInZone(SolidRigid* p) {
		return ((p->_pose.p.x < _zone.x_Max) && (p->_pose.p.x > _zone.x_Min) &&
			(p->_pose.p.y < _zone.y_Max) && (p->_pose.p.y > _zone.y_Min) &&
			(p->_pose.p.z < _zone.z_Max) && (p->_pose.p.z > _zone.z_Min));
	}
};

