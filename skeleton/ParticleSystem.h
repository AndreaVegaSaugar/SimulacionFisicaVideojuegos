#pragma once
#include <list>
#include "GaussianParticleGenerator.h"
#include "UniformParticleGenerator.h"


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
	ParticleGenerator* _firework_generator; // This generator is only to shoot the firework!!
	//std::vector<Firework*> _firework_pool; // Fireworks to be used as models!
	Zone _zone;
	Vector3 _gravity;
	void onParticleDeath(Particle* p);
	void createFireworkSystem(); 
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
	void generateFirework(unsigned firework_type); 
};

