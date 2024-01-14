#pragma once
#include "ParticleGenerator.h"
#include <random>

class UniformParticleGenerator : public ParticleGenerator {

protected:
	Vector4 _colorFrutos;
	Vector3 _pos_max, _vel_max, _pos_min, _vel_min;
	std::uniform_real_distribution<float>* pos_x;
	std::uniform_real_distribution<float>* pos_y;
	std::uniform_real_distribution<float>* pos_z;
	std::uniform_real_distribution<float>* vel_x;
	std::uniform_real_distribution<float>* vel_y;
	std::uniform_real_distribution<float>* vel_z;
	std::uniform_int_distribution<int> r;

public:
	UniformParticleGenerator(std::string name, Vector3 pos_max, Vector3 pos_min, Vector3 vel_max, Vector3 vel_min, int n_particles) : ParticleGenerator(), _pos_max(pos_max), _vel_max(vel_max), _pos_min(pos_min), _vel_min(vel_min) {
		_name = name;
		setNParticles(n_particles);

		pos_x = new std::uniform_real_distribution<float>(_pos_min.x, _pos_max.x);
		pos_y = new std::uniform_real_distribution<float>(_pos_min.y, _pos_max.y);
		pos_z = new std::uniform_real_distribution<float>(_pos_min.z, _pos_max.z);

		vel_x = new std::uniform_real_distribution<float>(_vel_min.x, _vel_max.x);
		vel_y = new std::uniform_real_distribution<float>(_vel_min.y, _vel_max.y);
		vel_z = new std::uniform_real_distribution<float>(_vel_min.z, _vel_max.z);
	}
	UniformParticleGenerator(PxScene* scene, PxPhysics* physics, std::string name, Vector3 pos_max, Vector3 pos_min, Vector3 vel_max, Vector3 vel_min, int n_solidRigids, Vector4 colorFrutos) : ParticleGenerator(scene, physics), _pos_max(pos_max), _vel_max(vel_max), _pos_min(pos_min), _vel_min(vel_min) {
		_name = name;
		_colorFrutos = colorFrutos;
		setNSolidRigids(n_solidRigids);
		
		pos_x = new std::uniform_real_distribution<float>(_pos_min.x, _pos_max.x);
		pos_y = new std::uniform_real_distribution<float>(_pos_min.y, _pos_max.y);
		pos_z = new std::uniform_real_distribution<float>(_pos_min.z, _pos_max.z);

		vel_x = new std::uniform_real_distribution<float>(_vel_min.x, _vel_max.x);
		vel_y = new std::uniform_real_distribution<float>(_vel_min.y, _vel_max.y);
		vel_z = new std::uniform_real_distribution<float>(_vel_min.z, _vel_max.z);

		r = std::uniform_int_distribution<int>(0, 20);
	}

	~UniformParticleGenerator();
	virtual list<Entity*> generateParticles() override;
	virtual list<Entity*> generateSolidRigids() override;
};

