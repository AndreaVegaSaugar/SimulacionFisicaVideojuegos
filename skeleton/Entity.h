#pragma once
#include "RenderUtils.hpp"
#include <iostream>
#include <list>

using namespace physx;

enum Shape{SPHERE, CUBE};

struct Zone {
	float x_Max, x_Min;
	float y_Max, y_Min;
	float z_Max, z_Min;
};

// clase padre de la que heredan Particle y SolidRigid, contiene sus metodos y propiedades comunes
class Entity
{
protected:
	RenderItem* renderItem = nullptr;

public:
	PxTransform _pose;
	Vector3 _vel;
	Vector3 _size;
	Vector3 _force = { 0 , 0 , 0 };
	double _duration;
	float _mass;
	Shape _shape;
	Vector4 _color;
	bool _isModel;

	bool alive = true;
	double _auxDuration = 0;

	virtual void integrate(double t) = 0;
	virtual inline void addForce(Vector3 f) = 0;
	virtual inline Entity* clone() = 0;
	virtual inline bool isAlive() { return alive; };
	virtual inline RenderItem* getRenderItem() { return renderItem; };
	virtual inline int getVolume() { return (_size.x * _size.y * _size.z); };
	virtual std::list<Entity*> onDeath() { std::list<Entity*> l; return l; };
	Entity() {};
	virtual ~Entity() {}

	bool checkCollision(Entity* other){
		return ((other->_pose.p.x + other->_size.x) >= (_pose.p.x - _size.x) && (other->_pose.p.x - other->_size.x) <= (_pose.p.x + _size.x) &&
				(other->_pose.p.y + other->_size.y) >= (_pose.p.y - _size.y) && (other->_pose.p.y - other->_size.y) <= (_pose.p.y + _size.y) &&
				(other->_pose.p.z + other->_size.z) >= (_pose.p.z - _size.z) && (other->_pose.p.z - other->_size.z) <= (_pose.p.z + _size.z));
	}
};

