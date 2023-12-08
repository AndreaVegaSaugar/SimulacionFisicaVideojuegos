#include "SolidRigid.h"

SolidRigid::SolidRigid(PxScene* scene, PxPhysics* physics, Vector3 pos, Vector3 vel, double duration, float mass, float size, Vector4 color, bool isModel) {
	_scene = scene;
	_physics = physics;
	_vel = vel;
	_duration = duration;
	_pose = PxTransform(pos);
	_mass = mass;
	_size = size;
	_color = color;
	_isModel = isModel;
	
	_rD = _physics->createRigidDynamic(_pose);
	_rD->setLinearVelocity(_vel);
	_rD->setAngularVelocity({ 0, 0, 0 });
	PxShape* _shape = CreateShape(PxBoxGeometry(_size, _size, _size));
	_rD->attachShape(*_shape);
	PxRigidBodyExt::updateMassAndInertia(*_rD, _mass);

	if (!_isModel) {
		renderItem = new RenderItem(_shape, _rD, _color);
	} 

	_scene->addActor(*_rD);
}

SolidRigid::~SolidRigid() {
	if (!_isModel) renderItem->release();
	_rD->release();
}

void SolidRigid::integrate(double t) {
	if (alive) {
		auxDuration += t;
		alive = auxDuration < _duration;
		_pose = _rD->getGlobalPose();
		_vel = _rD->getLinearVelocity();
	}
}