#include "SpringForceGenerator.h"

SpringForceGenerator::SpringForceGenerator(double k, double resting_length, Entity* other) : ForceGenerator(){
	_k = k;
	_resting_length = resting_length;
	_other = other;
}

SpringForceGenerator::~SpringForceGenerator() {

}

void SpringForceGenerator::updateForce(Entity* particle, double t) {
	Vector3 relative_pos_vector = _other->_pose.p - particle->_pose.p;

	const float lenght = relative_pos_vector.normalize();
	const float delta_x = lenght - _resting_length;

	Vector3 force;
	force = relative_pos_vector * delta_x * _k;
	particle->addForce(force);
}