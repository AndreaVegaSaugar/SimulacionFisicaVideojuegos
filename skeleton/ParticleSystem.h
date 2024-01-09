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
#include "Gun.h"

using namespace std;

class ParticleSystem
{
protected:
	PxScene* _scene;
	PxPhysics* _physics;
	list<Entity*> _entities;
	list<ParticleGenerator*> _particle_generators;
	list<ParticleGenerator*> _solidRigid_generators;
	FireworkGenerator* _firework_generator = nullptr;
	list<ForceGenerator*> _force_generators;
	list<ExplosionGenerator*> _explosion_generators;
	ParticleForceRegistry* _particle_force_registry;
	Zone _zone;
	Gun* _gun;
	GravityForceGenerator* _gravityGen;
	SpringForceGenerator* _spring;
	ElasticBandGenerator* _elasticBand;
	AnchoredSpring* _anchoredSpring;
	BuoyancyForceGenerator* _buoyancy;

	bool isInZone(Entity* p) {
		return ((p->_pose.p.x < _zone.x_Max) && (p->_pose.p.x > _zone.x_Min) &&
			(p->_pose.p.y < _zone.y_Max) && (p->_pose.p.y > _zone.y_Min) &&
			(p->_pose.p.z < _zone.z_Max) && (p->_pose.p.z > _zone.z_Min));
	}

public:
	ParticleSystem(PxScene* scene, PxPhysics* physics);
	~ParticleSystem();
	void update(double t);
	void shoot(Vector3 dir, Vector3 pos);
	ParticleGenerator* getParticleGenerator(const string& name); 
	FireworkGenerator* getFireworkGenerator() { return _firework_generator; };
	/*void generateFirework();
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
	void addMassToBuoyancy();*/
};

