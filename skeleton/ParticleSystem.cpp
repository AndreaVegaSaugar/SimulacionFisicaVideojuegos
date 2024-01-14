#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(PxScene* scene, PxPhysics* physics) {
	_zone.x_Max = 150; _zone.x_Min = -150; _zone.y_Max = 150; _zone.y_Min = -50; _zone.z_Max = 150; _zone.z_Min = -150;
	_scene = scene; _physics = physics;
	_state = INTRO;

	fondoUIIntro = new SolidRigid(_scene, _physics, { 0.0, 0.25, -2.5 }, CUBE, { 1.1, 0.5, 0.001 }, { 255, 255, 255, 1 });
	_UI.push_back(fondoUIIntro);

	_particle_force_registry = new ParticleForceRegistry();

	_gravityGen = new GravityForceGenerator(Vector3(0, -10, 0));
	_force_generators.push_back(_gravityGen);
	generateWind();
	_firework_generator = new FireworkGenerator();

	_gun = new Gun(scene, physics, RIFLE);
}

ParticleSystem::~ParticleSystem() {
	deleteDecorations();
	deleteGenerators();
	deleteForceGenerators();
	deleteEntities();
	deleteUI();
	deleteBullets();
	deleteFireworks();
	delete _particle_force_registry;
	if (_gun != nullptr) delete _gun;
	if (_firework_generator != nullptr) delete _firework_generator;
}

void ParticleSystem::startGame() {
	deleteFireworks();
	deleteUI();
	_state = PLAY;
	lives = 3;
	score = 0;
	generateUI();
	setDecoration();
	_elfGenerator = new UniformParticleGenerator(_scene, _physics, "elfGenerator", Vector3(40, -20, -60), Vector3(-40, -20, -60), Vector3(10, 30, 0), Vector3(-10, 15, 0), 1);
	_solidRigid_generators.push_back(_elfGenerator);
	_cloudGenerator = new GaussianParticleGenerator("cloudGenerator", Vector3(3, 5, 3), Vector3(0.01, 0.01, 0.01), Vector3(100, 40, -80), Vector3(0.01, 0.01, 0.01), 1);
	_particle_generators.push_back(_cloudGenerator);
}

void ParticleSystem::checkCollisions(Entity* bala) {
	for (auto ot = _entities.begin(); ot != _entities.end(); ++ot) {
		if (bala->isAlive() && (*ot)->isAlive() && (*ot)->checkCollision(bala)) {
			(*ot)->alive = false;
			bala->alive = false;
			score++;
			generateFirework((*ot)->_pose.p);
		}
	}
}

void ParticleSystem::loseLife() {
	lives--;
	if (lives == 2) { 
		livesP3->getRenderItem()->color = blanco;
		cleanScene();
	}
	else if (lives == 1) {
		livesP2->getRenderItem()->color = blanco;
		cleanScene();
	}
	if (lives <= 0) {
		eraseScene();
	}
}

void ParticleSystem::eraseScene() {
	_state = RETRY;

	deleteDecorations();
	deleteGenerators();
	deleteForceGenerators();
	deleteEntities();
	deleteUI();
	deleteBullets();
	deleteFireworks();

	_gravityGen = new GravityForceGenerator(Vector3(0, -10, 0));
	_force_generators.push_back(_gravityGen);
	generateWind();

	fondoUIRetry = new SolidRigid(_scene, _physics, { 0.0, 0.25, -2.5 }, CUBE, { 0.8, 0.4, 0.001 }, { 0, 0, 0, 1 });
	_UI.push_back(fondoUIRetry);

	for (int i = 0; i < 10; ++i) {
		generateFirework({ float(rand() % 10) - 5 , float(rand() % 10) - 5, -20 });
	}
}

void ParticleSystem::cleanScene() {
	deleteEntities();
	deleteBullets();
	deleteFireworks();
}

void ParticleSystem::update(double t) {
	_gun->integrate(t);
	_particle_force_registry->updateForces(t);

	for (auto it = _entities.begin(); it != _entities.end();) {
		bool zona = isInZone(*it);
		if ((*it)->isAlive() && zona) {
			(*it)->integrate(t);
			++it;
		}
		else {
			_particle_force_registry->deleteParticleRegistry((*it));
			auto ot = (*it)->onDeath();
			auto ut = _entities.end();
			_entities.splice(ut, ot);
			delete (*it);
			it = _entities.erase(it);
			if (!zona) { loseLife(); return; }
		}
	}
	for (auto it = _balas.begin(); it != _balas.end();) {
		if ((*it)->isAlive() && isInZone(*it)) {
			(*it)->integrate(t);
			checkCollisions(*it);
			++it;
		}
		else {
			_particle_force_registry->deleteParticleRegistry((*it));
			delete (*it);
			it = _balas.erase(it);
		}
	}
	for (auto it = _UI.begin(); it != _UI.end();) {
		if ((*it)->isAlive() && isInZone(*it)) {
			(*it)->integrate(t);
			++it;
		}
		else {
			_particle_force_registry->deleteParticleRegistry((*it));
			delete (*it);
			it = _UI.erase(it);
		}
	}
	for (auto it = _fireworks.begin(); it != _fireworks.end();) {
		if ((*it)->isAlive() && isInZone(*it)) {
			(*it)->integrate(t);
			++it;
		}
		else {
			auto ot = (*it)->onDeath();
			auto ut = _fireworks.end();
			_fireworks.splice(ut, ot);
			delete (*it);
			it = _fireworks.erase(it);
		}
	}
	for (ParticleGenerator* pG : _particle_generators) {
		pG->auxTimeP += t;
		if (pG->auxTimeP >= pG->generationTimeP) {
			auto particleList = pG->generateParticles();
			_particle_force_registry->addParticleListRegistrySingleGen(particleList, _windGen);
			for (Entity* s : particleList) {
				pG->auxTimeP = 0;
			}
			auto it = _UI.begin();
			_UI.splice(it, particleList);
		}
	}
	for (ParticleGenerator* sG : _solidRigid_generators) {
		sG->auxTimeS += t;
		if (sG->auxTimeS >= sG->generationTimeS) {
			auto solidRigidList = sG->generateSolidRigids();
			_particle_force_registry->addParticleListRegistrySingleGen(solidRigidList, _gravityGen);
			for (Entity* s : solidRigidList) {
				sG->auxTimeS = 0;
			}
			auto it = _entities.begin();
			_entities.splice(it, solidRigidList);
		}
	}
}

void ParticleSystem::shoot(Vector3 dir, Vector3 pos) {
	auto balas = _gun->shoot(dir, pos);
	_particle_force_registry->addParticleListRegistrySingleGen(balas, _gravityGen);
	auto it = _balas.begin();
	_balas.splice(it, balas);
}

void ParticleSystem::changeWeapon() {
	if (_state == PLAY) {
		if (_gun->getActiveWeapon() == RIFLE) {
			rifleP1->getRenderItem()->color = blanco;
			rifleP2->getRenderItem()->color = blanco;
			shotgunP1->getRenderItem()->color = rojo;
			shotgunP2->getRenderItem()->color = rojo;
		}
		else {
			rifleP1->getRenderItem()->color = rojo;
			rifleP2->getRenderItem()->color = rojo;
			shotgunP1->getRenderItem()->color = blanco;
			shotgunP2->getRenderItem()->color = blanco;
		}
		_gun->changeWeapon();
	}
}

void ParticleSystem::generateFirework(Vector3 pos) {
	Entity* p = _firework_generator->shoot(pos);
	_fireworks.push_back(p);
}

void ParticleSystem::generateWind() {
	_windGen = new ParticleDragGenerator(2, 0, Vector3(-20, 0, 0));
	_force_generators.push_back(_windGen);
}
//
//void ParticleSystem::generateTornado() {
//	auto whirlGen = new WhirlwindGenerator(1, 2, 0, Vector3(0, 20, 0));
//	_force_generators.push_back(whirlGen);
//}
//
//void ParticleSystem::generateExplosion() {
//	std::list<ForceGenerator*> aux;
//	auto explosionGen = new ExplosionGenerator(Vector3(0, 20, 0), 5, 10000, 500, 20);
//	_particle_force_registry->addParticleListRegistrySingleGen(_particles, explosionGen);
//	_explosion_generators.push_back(explosionGen);
//}
//

void ParticleSystem::generateUI() {
	SolidRigid* fondoUILives = new SolidRigid(_scene, _physics, { 2.22, 1.4, -2.5 }, CUBE, { 0.45, 0.2, 0.001 }, { 255, 255, 255, 1 });
	_UI.push_back(fondoUILives);
	generateUILives();
	SolidRigid* fondoUISprings = new SolidRigid(_scene, _physics, { -2.20, -1.2, -2.5 }, CUBE, { 0.3, 0.1, 0.001 }, { 255, 255, 255, 1 });
	_UI.push_back(fondoUISprings);
	generateUISprings();
	SolidRigid* fondoUIScore = new SolidRigid(_scene, _physics, { -2.22, 1.4, -2.5 }, CUBE, { 0.35, 0.2, 0.001 }, { 255, 255, 255, 1 });
	_UI.push_back(fondoUIScore);
}

void ParticleSystem::generateUILives() {
	livesP1 = new Particle({ 0.85, 0.538, -1 }, { 0, 0, 0 }, 1, -1, 1, CUBE, { 0.02, 0.02, 0.02 }, rojo, false);
	livesP2 = new Particle({ 0.92, 0.538, -1 }, { 0, 0, 0 }, 1, -1, 1, CUBE, { 0.02, 0.02, 0.02 }, rojo, false);
	livesP3 = new Particle({ 0.99, 0.538, -1 }, { 0, 0, 0 }, 1, -1, 1, CUBE, { 0.02, 0.02, 0.02 }, rojo, false);
	_UI.push_back(livesP1); _UI.push_back(livesP2); _UI.push_back(livesP3);
}

void ParticleSystem::generateUISprings() {

	Vector4 colorRifle;
	if (_gun->getActiveWeapon() == RIFLE) colorRifle = rojo;
	else colorRifle = blanco;

	rifleP1 = new Particle({ -0.98, -0.47, -1 }, { 0, 0, 0 }, 1, -1, 1, SPHERE, {0.01, 0.01, 0.01 }, colorRifle, false);
	rifleP2 = new Particle({ -0.85, -0.47, -1 }, { 0, 0, 0 }, 1, -1, 1, SPHERE, { 0.01, 0.01, 0.01 }, colorRifle, false);
	SpringForceGenerator* springR1 = new SpringForceGenerator(10, 0.12, rifleP2);
	SpringForceGenerator* springR2 = new SpringForceGenerator(10, 0.12, rifleP1);
	_particle_force_registry->addRegistry(springR1, rifleP1); _particle_force_registry->addRegistry(springR2, rifleP2);
	_force_generators.push_back(springR1); _force_generators.push_back(springR2);
	_UI.push_back(rifleP1); _UI.push_back(rifleP2);

	Vector4 colorShotgun;
	if (_gun->getActiveWeapon() == SHOTGUN) colorShotgun = rojo;
	else colorShotgun = blanco;

	shotgunP1 = new Particle({ -0.98, -0.5, -1 }, { 0, 0, 0 }, 1, -1, 1, SPHERE, { 0.01, 0.01, 0.01 }, colorShotgun, false);
	shotgunP2 = new Particle({ -0.79, -0.5, -1 }, { 0, 0, 0 }, 1, -1, 1, SPHERE, { 0.01, 0.01, 0.01 }, colorShotgun, false);
	SpringForceGenerator* springS1 = new SpringForceGenerator(10, 0.18, shotgunP2);
	SpringForceGenerator* springS2 = new SpringForceGenerator(10, 0.18, shotgunP1);
	_particle_force_registry->addRegistry(springS1, shotgunP1); _particle_force_registry->addRegistry(springS2, shotgunP2);
	_force_generators.push_back(springS1); _force_generators.push_back(springS2);
	_UI.push_back(shotgunP1); _UI.push_back(shotgunP2);
}

void ParticleSystem::setDecoration() {
	color = std::uniform_real_distribution<float>(0.0, 1.0);
	colorFrutos = { color(_mt), color(_mt), color(_mt), 1 };
	_arbustos.push_back(new Arbusto(_scene, _physics, { -45, -20, -50 }, { 15, 7, 5 }, colorFrutos));
	_arbustos.push_back(new Arbusto(_scene, _physics, { -20, -22.5, -50 }, { 10, 6.5, 5 }, colorFrutos));
	_arbustos.push_back(new Arbusto(_scene, _physics, { 0, -20, -50 }, { 10, 7, 5 }, colorFrutos));
	_arbustos.push_back(new Arbusto(_scene, _physics, { 20, -22.5, -50 }, { 10, 6.5, 5 }, colorFrutos));
	_arbustos.push_back(new Arbusto(_scene, _physics, { 45, -20, -50 }, { 15, 7, 5 }, colorFrutos));

	//experimento
	_arbustos.push_back(new Arbusto(_scene, _physics, { -64, 0, -60 }, { 1, 100, 1 }, colorFrutos));
	_arbustos.push_back(new Arbusto(_scene, _physics, { 64, 0, -60 }, { 1, 100, 1 }, colorFrutos));
}

void ParticleSystem::deleteGenerators() {
	for (auto it = _particle_generators.begin(); it != _particle_generators.end();) {
		delete (*it);
		it = _particle_generators.erase(it);
	}
	for (auto it = _solidRigid_generators.begin(); it != _solidRigid_generators.end();) {
		delete (*it);
		it = _solidRigid_generators.erase(it);
	}
}
void ParticleSystem::deleteForceGenerators() {
	for (auto it = _force_generators.begin(); it != _force_generators.end();) {
		_particle_force_registry->deleteGeneratorRegistry((*it));
		delete (*it);
		it = _force_generators.erase(it);
	}
}
void ParticleSystem::deleteBullets() {
	for (auto it = _balas.begin(); it != _balas.end();) {
		_particle_force_registry->deleteParticleRegistry((*it));
		delete (*it);
		it = _balas.erase(it);
	}
}
void ParticleSystem::deleteDecorations() {
	for (auto it = _arbustos.begin(); it != _arbustos.end();) {
		delete (*it);
		it = _arbustos.erase(it);
	}
}
void ParticleSystem::deleteUI() {
	for (auto it = _UI.begin(); it != _UI.end();) {
		_particle_force_registry->deleteParticleRegistry((*it));
		delete (*it);
		it = _UI.erase(it);
	}
}
void ParticleSystem::deleteEntities() {
	for (auto it = _entities.begin(); it != _entities.end();) {
		_particle_force_registry->deleteParticleRegistry((*it));
		delete (*it);
		it = _entities.erase(it);
	}
}
void ParticleSystem::deleteFireworks() {
	for (auto it = _fireworks.begin(); it != _fireworks.end();) {
		delete (*it);
		it = _fireworks.erase(it);
	}
}


ParticleGenerator* ParticleSystem::getParticleGenerator(const string& name) {
	for (ParticleGenerator* pG : _particle_generators) {
		if (pG->getName() == name) return pG;
	}
}