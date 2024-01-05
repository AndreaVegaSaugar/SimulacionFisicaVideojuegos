#pragma once
#include "SolidRigid.h"

class SolidRigidForceGenerator {
protected:
	SolidRigidForceGenerator() {};
	Zone _zone;
	Vector3 _center;

public:
	std::string _name;
	bool _alive = true;
	virtual void updateForce(SolidRigid* sR, double t) = 0;
	double _t = 0.0; // If starting negative --> eternal
	double _duration = -1e10;
	inline bool updateTime(double t) {
		_t += t;
		return _t < _duration || _duration < 0.0; // Devuelve true si ya era cero o si es positivo
	}
	virtual ~SolidRigidForceGenerator() {}

	bool isInZone(SolidRigid* p, Zone _zone) {
		return ((p->_pose.p.x < _zone.x_Max) && (p->_pose.p.x > _zone.x_Min) &&
			(p->_pose.p.y < _zone.y_Max) && (p->_pose.p.y > _zone.y_Min) &&
			(p->_pose.p.z < _zone.z_Max) && (p->_pose.p.z > _zone.z_Min));
	}
};
