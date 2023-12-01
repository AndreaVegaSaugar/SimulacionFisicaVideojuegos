#pragma once
#include <list>
#include "GaussianParticleGenerator.h"
#include "UniformParticleGenerator.h"
#include "FireworkGenerator.h"
#include "GravityForceGenerator.h"
#include "WhirlwindGenerator.h"
#include "ExplosionGenerator.h"
#include "AnchoredSpring.h"
#include "ElasticBandGenerator.h"
#include "ParticleForceRegistry.h"
#include "BuoyancyForceGenerator.h"

using namespace std;

class ParticleSystem
{
protected:
	list<Particle*> _particles;
	list<ParticleGenerator*> _particle_generators;
	FireworkGenerator* _firework_generator = nullptr;
	list<ForceGenerator*> _force_generators;
	list<ExplosionGenerator*> _explosion_generators;
	ParticleForceRegistry* _particle_force_registry;
	Zone _zone;
	GravityForceGenerator* _gravityGen;
	
	SpringForceGenerator* _spring;
	ElasticBandGenerator* _elasticBand;
	AnchoredSpring* _anchoredSpring;
	BuoyancyForceGenerator* _buoyancy;
	Particle* _springParticle;
	Particle* _elasticBandParticle;
	Particle* _anchoredSpringParticle;
	Particle* _buoyancyParticle;

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
	void generateExplosion();
	void generateWind();
	void generateTornado();

	void generateSpring();
	void generateElasticBand();
	void generateAnchoredSpring();
	void generateBuoyancyGenerator();

	void changeElasticBandConstant(int k);
	void addForceToElasticBand();
	void changeSpringConstant(int k);
	void addForceToSpring();
	void changeAnchoredSpringConstant(int k);
	void addForceToAnchoredSpring();
	void addMassToBuoyancy();
};

