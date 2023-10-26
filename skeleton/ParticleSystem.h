#pragma once
#include <list>
#include "GaussianParticleGenerator.h"
#include "UniformParticleGenerator.h"
#include "FireworkGenerator.h"

using namespace std;

struct Zone {
	float x_Max, x_Min;
	float y_Max, y_Min;
	float z_Max, z_Min;
};

class ParticleSystem
{
protected:
	list<Particle*> _particles;
	list<ParticleGenerator*> _particle_generators;
	FireworkGenerator* _firework_generator = nullptr;
	Zone _zone;
	Vector3 _gravity;

	bool isInZone(Particle* p) {
		return ((p->_pose.p.x < _zone.x_Max) && (p->_pose.p.x > _zone.x_Min) &&
			(p->_pose.p.y < _zone.y_Max) && (p->_pose.p.y > _zone.y_Min) &&
			(p->_pose.p.z < _zone.z_Max) && (p->_pose.p.z > _zone.z_Min));
	}

public:
	ParticleSystem(const Vector3& g = { 0.0f, -10.0f, 0.0f});
	~ParticleSystem();
	void update(double t);
	ParticleGenerator* getParticleGenerator(const string& name); 
	FireworkGenerator* getFireworkGenerator() { return _firework_generator; };
	void generateFirework();
};

