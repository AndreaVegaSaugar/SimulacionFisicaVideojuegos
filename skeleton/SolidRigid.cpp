#include "SolidRigid.h"

SolidRigid::SolidRigid(physx::PxScene* scene, physx::PxPhysics* physics, Vector3 pos, Vector3 vel, double duration, float mass, Shape shape, Vector3 size, Vector4 color, bool isModel):Entity() {
	_scene = scene;
	_physics = physics;
	_vel = vel;
	_duration = duration;
	_pose = PxTransform(pos);
	_mass = mass;
	_shape = shape;
	_size = size;
	_color = color;
	_isModel = isModel;
	
	_rD = _physics->createRigidDynamic(_pose);
	_rD->setLinearVelocity(_vel);
	_rD->setAngularVelocity({ 0, 0, 0 });

	PxShape* auxShape;
	if (shape == SPHERE) auxShape = CreateShape(PxSphereGeometry(_size.x));
	else auxShape = CreateShape(PxBoxGeometry(_size));

	_rD->attachShape(*auxShape);
	PxRigidBodyExt::updateMassAndInertia(*_rD, _mass);

	if (!_isModel) {
		renderItem = new RenderItem(auxShape, _rD, _color);
	} 

	_scene->addActor(*_rD);
}

SolidRigid::SolidRigid(physx::PxScene* scene, physx::PxPhysics* physics, Vector3 pos, Shape shape, Vector3 size, Vector4 color) :Entity() {
	_scene = scene;
	_physics = physics;
	_pose = PxTransform(pos);
	_shape = shape;
	_size = size;
	_color = color;

	_rS = _physics->createRigidStatic(_pose);

	PxShape* auxShape;
	if (shape == SPHERE) auxShape = CreateShape(PxSphereGeometry(_size.x));
	else auxShape = CreateShape(PxBoxGeometry(_size));

	_rS->attachShape(*auxShape);

	renderItem = new RenderItem(auxShape, _rS, _color);
	

	_scene->addActor(*_rS);
}

SolidRigid::~SolidRigid() {
	if (!_isModel) renderItem->release();
	if(_rD != nullptr) _rD->release();
	if (_rS != nullptr) _rD->release();
}

void SolidRigid::integrate(double t) {
	if (_rS == nullptr && alive) {
		if (_duration != -1) {
			_auxDuration += t;
			alive = _auxDuration < _duration;
		}
		_pose = _rD->getGlobalPose();
		_vel = _rD->getLinearVelocity();
	}
}