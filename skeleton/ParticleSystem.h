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
#include "Arbusto.h"

using namespace std;

enum gameState { INTRO = 0, PLAY = 1, RETRY = 2 };

class ParticleSystem
{
protected:

	gameState _state = INTRO;
	PxScene* _scene;
	PxPhysics* _physics;
	list<Entity*> _UI;
	list<Entity*> _entities;
	list<Entity*> _balas;
	list<Entity*> _fireworks;
	list<ParticleGenerator*> _particle_generators;
	list<ParticleGenerator*> _solidRigid_generators;
	FireworkGenerator* _firework_generator = nullptr;
	list<ForceGenerator*> _force_generators;
	list<ExplosionGenerator*> _explosion_generators;
	ParticleForceRegistry* _particle_force_registry;
	Zone _zone;
	Gun* _gun = nullptr;
	GravityForceGenerator* _gravityGen;
	SpringForceGenerator* _spring;
	ElasticBandGenerator* _elasticBand;
	AnchoredSpring* _anchoredSpring;
	ParticleGenerator* _elfGenerator;
	ParticleGenerator* _cloudGenerator;
	ParticleDragGenerator* _windGen;
	//BuoyancyForceGenerator* _buoyancy;

	Particle* rifleP1;
	Particle* rifleP2;
	Particle* shotgunP1;
	Particle* shotgunP2;

	Vector4 blanco = { 255, 255, 255, 1 };
	Vector4 rojo = { 255, 0, 0, 1 };
	Vector4 colorFrutos;
	std::uniform_real_distribution<float> color;
	std::random_device rd{};
	std::mt19937 _mt{ rd() };
	vector<Arbusto*> _arbustos;

	int lives = 3;
	Particle* livesP1;
	Particle* livesP2;
	Particle* livesP3;

	SolidRigid* fondoUIIntro = nullptr;
	SolidRigid* fondoUIRetry = nullptr;

	int score = 0;

	bool isInZone(Entity* p) {
		return ((p->_pose.p.x < _zone.x_Max) && (p->_pose.p.x > _zone.x_Min) &&
			(p->_pose.p.y < _zone.y_Max) && (p->_pose.p.y > _zone.y_Min) &&
			(p->_pose.p.z < _zone.z_Max) && (p->_pose.p.z > _zone.z_Min));
	}

public:
	ParticleSystem(PxScene* scene, PxPhysics* physics);
	virtual ~ParticleSystem();
	void update(double t);
	void shoot(Vector3 dir, Vector3 pos);
	void startGame();
	Gun* getGun() { return _gun; }
	ParticleGenerator* getParticleGenerator(const string& name); 
	FireworkGenerator* getFireworkGenerator() { return _firework_generator; };
	void changeWeapon();
	void generateUI();
	void generateUISprings();
	void generateUILives();
	void setDecoration();
	void checkCollisions(Entity* e);
	void loseLife();
	void eraseScene();
	void cleanScene();
	int getScore() { return score; };
	gameState getGameState() { return _state; };
	void deleteGenerators();
	void deleteForceGenerators();
	void deleteBullets();
	void deleteDecorations();
	void deleteUI();
	void deleteEntities();
	void deleteFireworks();


	void generateFirework(Vector3 pos);
	void generateExplosion(Vector3 pos);
	void generateWind();
	//void generateTornado();

	//void generateElasticBand();
	//void generateAnchoredSpring();
	//void generateBuoyancyGenerator();

	//void changeElasticBandConstant(int k);
	//void addForceToElasticBand();
	//void changeSpringConstant(int k);
	//void addForceToSpring();
	//void changeAnchoredSpringConstant(int k);
	//void addForceToAnchoredSpring();
	//void addMassToBuoyancy();
};

