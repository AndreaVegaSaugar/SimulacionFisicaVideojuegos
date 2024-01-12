#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(PxScene* scene, PxPhysics* physics) {
	_zone.x_Max = 500; _zone.x_Min = -500; _zone.y_Max = 500; _zone.y_Min = -100; _zone.z_Max = 500; _zone.z_Min = -500;
	_scene = scene; _physics = physics;

	_particle_force_registry = new ParticleForceRegistry();

	_gravityGen = new GravityForceGenerator(Vector3(0, -10, 0));
	_force_generators.push_back(_gravityGen);
	//Entity* aux = new Particle({ 0,0,0 }, { 0,0,0 }, 0,1000, 0, SPHERE,{1,1,1},{1,1,1,1},false);

	//_particle_generators.push_back(new UniformParticleGenerator("fuente", Vector3(1, 5, 1), Vector3(-1, 5, -1), Vector3(10, 30, 10), Vector3(-10, 30, -10), 1));
	//_particle_generators.push_back(new GaussianParticleGenerator("fuente", Vector3(1, 1, 1), Vector3(30, 1, 30), Vector3(1, 1, 1), Vector3(0, 30, 0), 1));

	_gun = new Gun(scene, physics, RIFLE);
}

ParticleSystem::~ParticleSystem() {
	if (_gun != nullptr) delete _gun;
	for (auto it = _particle_generators.begin(); it != _particle_generators.end(); ++it) {
		delete (*it);
	}
	for (auto it = _force_generators.begin(); it != _force_generators.end(); ++it) {
		delete (*it);
	}
	if (_firework_generator != nullptr) delete _firework_generator;
}

void ParticleSystem::startGame() {
	generateUISprings();
	setDecoration();
	_elfGenerator = new UniformParticleGenerator(_scene, _physics, "elfGenerator", Vector3(40, -25, -60), Vector3(-40, -25, -60), Vector3(10, 10, 0), Vector3(-10, 5, 0), 1);
	_solidRigid_generators.push_back(_elfGenerator);

}

void ParticleSystem::checkCollisions(Entity* e) {
	for (auto ot = _balas.begin(); ot != _balas.end(); ++ot) {
		//std::cout << "system2: " << (*ot)->_pose.p.x << " " << (*ot)->_pose.p.y << " " << (*ot)->_pose.p.z << std::endl;
		if ((*ot)->checkCollision(e)) {
			(*ot)->alive = false;
			e->alive = false;
			//cout << "acierto" << endl;
		}
	}
}

void ParticleSystem::update(double t) {
	_gun->integrate(t);
	_particle_force_registry->updateForces(t);

	for (auto it = _entities.begin(); it != _entities.end();) {
		if (_balas.size() > 0) { 
			//std::cout << "system1: " << (*_balas.begin())->_pose.p.x << " " << (*_balas.begin())->_pose.p.y << " " << (*_balas.begin())->_pose.p.z << std::endl;
			checkCollisions(*it); 
		}
		if ((*it)->isAlive() && isInZone(*it)) {
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
		}
	}
	for (auto it = _balas.begin(); it != _balas.end();) {
		if ((*it)->isAlive() && isInZone(*it)) {
			(*it)->integrate(t);
			//std::cout << "INTEGRATE BALAS: " << (*it)->_pose.p.x << " " << (*it)->_pose.p.y << " " << (*it)->_pose.p.z << std::endl;
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
	for (ParticleGenerator* pG : _particle_generators) {
		auto particleList = pG->generateParticles();
		_particle_force_registry->addParticleListRegistrySingleGen(particleList, _gravityGen);
		auto it = _entities.begin();
		_entities.splice(it, particleList);
	}
	for (ParticleGenerator* sG : _solidRigid_generators) {
		sG->auxTime += t;
		if (sG->auxTime >= sG->generationTime) {
			auto solidRigidList = sG->generateSolidRigids();
			_particle_force_registry->addParticleListRegistrySingleGen(solidRigidList, _gravityGen);
			for (Entity* s : solidRigidList) {
				sG->auxTime = 0;
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

	//std::cout << "BALAS SIZE: " << _balas.size() << std::endl;
}

void ParticleSystem::changeWeapon() {
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

//void ParticleSystem::generateFirework() {
//	Particle* p = _firework_generator->shoot();
//	_particles.push_back(p);
//}
//
//void ParticleSystem::generateWind() {
//	auto dragGen = new ParticleDragGenerator(2, 0, Vector3(20, 0, 0));
//	_force_generators.push_back(dragGen);
//}
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

void ParticleSystem::generateUISprings() {
	SolidRigid* fondoUI = new SolidRigid(_scene, _physics, { -2.20, -1.2, -2.5 }, CUBE, { 0.3, 0.1, 0.001 }, { 255, 255, 255, 1 });
	_UI.push_back(fondoUI);

	rifleP1 = new Particle({ -0.98, -0.47, -1 }, { 0, 0, 0 }, 1, -1, 1, SPHERE, {0.01, 0.01, 0.01 }, rojo, false);
	rifleP2 = new Particle({ -0.85, -0.47, -1 }, { 0, 0, 0 }, 1, -1, 1, SPHERE, { 0.01, 0.01, 0.01 }, rojo, false);
	SpringForceGenerator* springR1 = new SpringForceGenerator(10, 0.12, rifleP2);
	SpringForceGenerator* springR2 = new SpringForceGenerator(10, 0.12, rifleP1);
	_particle_force_registry->addRegistry(springR1, rifleP1); _particle_force_registry->addRegistry(springR2, rifleP2);
	_force_generators.push_back(springR1); _force_generators.push_back(springR2);
	_UI.push_back(rifleP1); _UI.push_back(rifleP2);

	shotgunP1 = new Particle({ -0.98, -0.5, -1 }, { 0, 0, 0 }, 1, -1, 1, SPHERE, { 0.01, 0.01, 0.01 }, blanco, false);
	shotgunP2 = new Particle({ -0.79, -0.5, -1 }, { 0, 0, 0 }, 1, -1, 1, SPHERE, { 0.01, 0.01, 0.01 }, blanco, false);
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
	_arbustos.push_back(new Arbusto(_scene, _physics, { -20, -25, -50 }, { 10, 6, 5 }, colorFrutos));
	_arbustos.push_back(new Arbusto(_scene, _physics, { 0, -22.5, -50 }, { 10, 6.5, 5 }, colorFrutos));
	_arbustos.push_back(new Arbusto(_scene, _physics, { 20, -20, -50 }, { 10, 7, 5 }, colorFrutos));
	_arbustos.push_back(new Arbusto(_scene, _physics, { 45, -22.5, -50 }, { 15, 6.5, 5 }, colorFrutos));

}

//
//void ParticleSystem::generateElasticBand() {
//	_elasticBandParticle = new Particle({ 50, 20, -5 }, { 0, 0, 0 }, 0.998, -1, 1, CUBE, {1, 1, 1}, {255, 0, 0, 1}, false);
//	Particle* p2 = new Particle({ 70, 20, -5 }, { 0, 0, 0 }, 0.998, -1, 1, CUBE, {1, 1, 1}, {255, 255, 0, 1}, false);
//	_elasticBand = new ElasticBandGenerator(1, 10, p2);
//	ElasticBandGenerator* f2 = new ElasticBandGenerator(1, 10, _elasticBandParticle);
//	//_particle_force_registry->addRegistry(_gravityGen, _elasticBandParticle); _particle_force_registry->addRegistry(_gravityGen, p2);
//	_particle_force_registry->addRegistry(_elasticBand, _elasticBandParticle); _particle_force_registry->addRegistry(f2, p2);
//	_force_generators.push_back(_elasticBand); _force_generators.push_back(f2);
//	_particles.push_back(_elasticBandParticle); _particles.push_back(p2);
//}
//
//void ParticleSystem::generateAnchoredSpring() {
//	_anchoredSpringParticle = new Particle({-55, 20, 0 }, { 0, 0, 0 }, 0.998, -1, 1, CUBE, {1, 1, 1}, {255, 0, 0, 1}, false);
//	_particle_force_registry->addRegistry(_gravityGen, _anchoredSpringParticle);
//	_anchoredSpring = new AnchoredSpring(1, 10, { -50, 20, 0 });
//	_particle_force_registry->addRegistry(_anchoredSpring, _anchoredSpringParticle);
//	_force_generators.push_back(_anchoredSpring);
//	_particles.push_back(_anchoredSpringParticle);
//}
//
//void ParticleSystem::generateBuoyancyGenerator() {
//	_buoyancyParticle = new Particle({ 0, 7, 0 }, { 0, 0, 0 }, 0.90, -1, 400, CUBE, { 2, 5, 2 }, { 255, 0, 0, 1 }, false);
//	Particle* pB2 = new Particle({ -15, 7, 0 }, { 0, 0, 0 }, 0.90, -1, 200, CUBE, { 5, 10, 5 }, { 255, 255, 0, 1 }, false);
//	Particle* pB3 = new Particle({ 15, 7, 0 }, { 0, 0, 0 }, 0.90, -1, 400, CUBE, { 1, 3, 1 }, { 255, 255, 0, 1 }, false);
//	_buoyancy = new BuoyancyForceGenerator(1, 1000, { 30, 1, 10 });
//	_particle_force_registry->addRegistry(_gravityGen, _buoyancyParticle); _particle_force_registry->addRegistry(_gravityGen, pB2); _particle_force_registry->addRegistry(_gravityGen, pB3);
//	_particle_force_registry->addRegistry(_buoyancy, _buoyancyParticle); _particle_force_registry->addRegistry(_buoyancy, pB2); _particle_force_registry->addRegistry(_buoyancy, pB3);
//	_particles.push_back(_buoyancyParticle); _particles.push_back(pB2); _particles.push_back(pB3);
//	_force_generators.push_back(_buoyancy);
//}
//
//void ParticleSystem::changeSpringConstant(int k) {
//	_spring->addK(k);
//}
//void ParticleSystem::changeAnchoredSpringConstant(int k) {
//	_anchoredSpring->addK(k);
//}
//void ParticleSystem::changeElasticBandConstant(int k) {
//	_elasticBand->addK(k);
//}
//
//void ParticleSystem::addForceToElasticBand() {
//	_elasticBandParticle->addForce({ 500, 0, 0 });
//}
//void ParticleSystem::addForceToSpring() {
//	_springParticle->addForce({ 500, 0, 0 });
//}
//void ParticleSystem::addMassToBuoyancy() {
//	_buoyancyParticle->_mass += 500;
//}
//void ParticleSystem::addForceToAnchoredSpring() {
//	_anchoredSpringParticle->addForce({ 500, 0, 0 });
//}

ParticleGenerator* ParticleSystem::getParticleGenerator(const string& name) {
	for (ParticleGenerator* pG : _particle_generators) {
		if (pG->getName() == name) return pG;
	}
}