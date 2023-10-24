#pragma once
#include <list>
#include <string>
#include "Particle.h"
#include <time.h>
#include <random>

using namespace std;

class ParticleGenerator {

protected:
	string _name;
	Vector3 _mean_vel, _origin; //_mean_pos;
	Particle* _model = nullptr; 
	int _n_particles = 1; // Number of particles for each generateParticles call(TODO: add randomness ? ? )
	double _generation_prob = 1.0; // IF 1.0 --> always produces particles
	std::mt19937 _mt;

public:
	ParticleGenerator(Vector3 gravity); //crear un modelo(?)
	string getName() { return _name; }
	inline void setOrigin(const Vector3& p) { _origin = p; }
	inline void setMeanVelocity(const Vector3& v) {
		_mean_vel
			= v;
	}
	inline Vector3 getMeanVelocity() const {
		return _mean_vel;
	}
	inline void setMeanDuration(double new_duration) {
		_model->_duration = new_duration;
	}
	//void setParticle(Particle* model) { _model = model; }; // solo sirve para cambiar del modelo desde fuera
	/*inline void setParticle(Particle* p, bool modify_pos_vel =
		true) {
		delete _model;
		_model = p->clone();
		if (modify_pos_vel) {
			_origin = p->_pose.p;
			_mean_vel = p->_vel;
		}
		_model->setPos({ -1000.0f, -1000.0f, -1000.0f });
	}*/
	inline void setNParticles(int n_p) { _n_particles = n_p; }
	virtual list<Particle*> generateParticles() = 0;
};

