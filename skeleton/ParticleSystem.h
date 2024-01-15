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
	// estado del juego
	gameState _state = INTRO;
	// escena y fisicas necesarias para los solidos rigidos
	PxScene* _scene = nullptr;
	PxPhysics* _physics = nullptr;
	// listas de entidades
	list<Entity*> _UI;
	list<Entity*> _entities;
	list<Entity*> _balas;
	list<Entity*> _fireworks;
	list<ParticleGenerator*> _particle_generators;
	list<ParticleGenerator*> _solidRigid_generators;
	list<ForceGenerator*> _force_generators;
	list<ExplosionGenerator*> _explosion_generators;
	// registro de fuerzas
	ParticleForceRegistry* _particle_force_registry = nullptr;
	// generadores de fuerzas
	GravityForceGenerator* _gravityGen = nullptr;
	SpringForceGenerator* _spring = nullptr;
	ParticleDragGenerator* _windGen = nullptr;
	// generadores de entidades
	FireworkGenerator* _firework_generator = nullptr;
	ParticleGenerator* _elfGenerator = nullptr;
	ParticleGenerator* _cloudGenerator = nullptr;
	Zone _zone;
	Gun* _gun = nullptr;

	// particulas y colores del nuelle
	Particle* rifleP1;
	Particle* rifleP2;
	Particle* shotgunP1;
	Particle* shotgunP2;
	Vector4 blanco = { 255, 255, 255, 1 };
	Vector4 rojo = { 255, 0, 0, 1 };

	// vector de arbustos y su color de frutos, generado aleatoriamente
	vector<Arbusto*> _arbustos;
	Vector4 colorFrutos;
	std::uniform_real_distribution<float> color;
	std::random_device rd{};
	std::mt19937 _mt{ rd() };

	// particulas que representan las vidas
	int lives = 3;
	Particle* livesP1;
	Particle* livesP2;
	Particle* livesP3;

	// solidos rigidos que resaltan el texto de la escena de intro y retry
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
	void changeWeapon();
	void generateUI();
	void generateUISprings();
	void generateUILives();
	void setDecoration();
	void checkCollisions(Entity* e);
	void loseLife();
	void eraseScene();
	void cleanScene();
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
	void generateGravity();
	int getScore() { return score; };
	Gun* getGun() { return _gun; }
	gameState getGameState() { return _state; };
	ParticleGenerator* getParticleGenerator(const string& name); 
	FireworkGenerator* getFireworkGenerator() { return _firework_generator; };
};

