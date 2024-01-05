#include "ElasticBandGenerator.h"
#include <iostream>

ElasticBandGenerator::ElasticBandGenerator(double k, double resting_length, Entity* other) : SpringForceGenerator(k, resting_length, other) {

}

void ElasticBandGenerator::updateForce(Entity* particle, double t) {
	Vector3 result = _other->_pose.p - particle->_pose.p;
	if (result.magnitude() > _resting_length) {
		SpringForceGenerator::updateForce(particle, t);
	}
}