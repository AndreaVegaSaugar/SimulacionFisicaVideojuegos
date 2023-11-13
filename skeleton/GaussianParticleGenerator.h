#pragma once
#include "ParticleGenerator.h"
#include <random>
#include <algorithm>

class GaussianParticleGenerator : public ParticleGenerator {

protected:
	Vector3 _std_dev_pos, _std_dev_vel, _mean_pos, _mean_vel;
	normal_distribution<float>* pos_x;
	normal_distribution<float>* pos_y;
	normal_distribution<float>* pos_z;
	normal_distribution<float>* vel_x; //{media, dev}
	normal_distribution<float>* vel_y;
	normal_distribution<float>* vel_z;

public:
	GaussianParticleGenerator(std::string name, Vector3 std_dev_pos, Vector3 std_dev_vel, Vector3 mean_pos, Vector3 mean_vel, int n_particles) : ParticleGenerator(), _std_dev_pos(std_dev_pos), _std_dev_vel(std_dev_vel), _mean_pos(mean_pos), _mean_vel(mean_vel) {
		_name = name;
		setNParticles(n_particles);

		pos_x = new std::normal_distribution<float>(mean_pos.x, std_dev_pos.x);
		pos_y = new std::normal_distribution<float>(mean_pos.y, std_dev_pos.y);
		pos_z = new std::normal_distribution<float>(mean_pos.z, std_dev_pos.z);

		vel_x = new std::normal_distribution<float>(mean_vel.x, std_dev_vel.x);
		vel_y = new std::normal_distribution<float>(mean_vel.y, std_dev_vel.y);
		vel_z = new std::normal_distribution<float>(mean_vel.z, std_dev_vel.z);
	}
	~GaussianParticleGenerator();
	virtual list<Particle*> generateParticles() override;
};

