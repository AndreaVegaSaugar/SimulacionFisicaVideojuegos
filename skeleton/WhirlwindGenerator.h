#pragma once
#include "ParticleDragGenerator.h"
#include <iostream>
#include <cmath>

class WhirlwindGenerator : public ParticleDragGenerator
{
public:
	WhirlwindGenerator(const float K, const float k1, const float k2, Vector3 wind) : ParticleDragGenerator(k1, k2, wind) { 
		_K = K; 
		_zone.x_Max = 200; _zone.x_Min = -200; _zone.y_Max = 200; _zone.y_Min = 0; _zone.z_Max = 200; _zone.z_Min = -200;
		_center = Vector3(abs(_zone.x_Max) - abs(_zone.x_Min), _zone.y_Min, abs(_zone.z_Max) - abs(_zone.z_Min));
	};
	void updateForce(Particle* particle, double t);

protected:
	float _K;
	Zone _zone;
	Vector3 _center;

	bool isInZone(Particle* p) {
		return ((p->_pose.p.x < _zone.x_Max) && (p->_pose.p.x > _zone.x_Min) &&
			(p->_pose.p.y < _zone.y_Max) && (p->_pose.p.y > _zone.y_Min) &&
			(p->_pose.p.z < _zone.z_Max) && (p->_pose.p.z > _zone.z_Min));
	}
};
