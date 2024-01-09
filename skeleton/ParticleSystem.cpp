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
	for (auto it = _particle_generators.begin(); it != _particle_generators.end(); ++it) {
		delete (*it);
	}
	if (_firework_generator != nullptr) delete _firework_generator;
}

void ParticleSystem::update(double t) {
	_gun->integrate(t);
	_particle_force_registry->updateForces(t);
	//for (auto it = _explosion_generators.begin(); it != _explosion_generators.end();) {
	//	if (!(*it)->updateTime(t)) {
	//		_particle_force_registry->deleteGeneratorRegistry(*it);
	//		delete (*it);
	//		it = _explosion_generators.erase(it);
	//		//std::cout << "borrado lista" << std::endl;
	//	}
	//	else ++it;
	//}
	for (auto it = _entities.begin(); it != _entities.end();) {
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
	for (ParticleGenerator* pG : _particle_generators) {
		auto particleList = pG->generateParticles();
		_particle_force_registry->addParticleListRegistry(particleList, _force_generators); 
		auto it = _entities.begin();
		_entities.splice(it, particleList);
	}
	/*for (ParticleGenerator* sG : _solidRigid_generators) {
		sG->auxTime += t;
		if (sG->auxTime >= sG->generationTime) {
			auto solidRigidList = sG->generateSolidRigids();
			_particle_force_registry->addParticleListRegistry(solidRigidList, _force_generators); 
			for (Entity* s : solidRigidList) {
				sG->auxTime = 0;
			}
			auto it = _entities.begin();
			_entities.splice(it, solidRigidList);
		}
	}*/
}

void ParticleSystem::shoot(Vector3 dir, Vector3 pos) {
	auto it = _gun->shoot(dir, pos);
	_particle_force_registry->addSingleParticleListRegistry(it, _force_generators);
	_entities.push_back(it);
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
//void ParticleSystem::generateSpring() {	
//	Particle* p1 = new Particle({ 50, 20, 5 }, { 0, 0, 0 }, 0.998, -1, 1, CUBE, {1, 1, 1}, {255, 255, 0, 1}, false);
//	_springParticle = new Particle({ 70, 20, 5 }, { 0, 0, 0 }, 0.998, -1, 1, CUBE, {1, 1, 1}, { 255, 0, 0, 1 }, false);
//	_spring = new SpringForceGenerator(1, 10, _springParticle);
//	SpringForceGenerator* f2 = new SpringForceGenerator(1, 10, p1);
//	//_particle_force_registry->addRegistry(_gravityGen, p1); _particle_force_registry->addRegistry(_gravityGen, p2);
//	_particle_force_registry->addRegistry(_spring, p1); _particle_force_registry->addRegistry(f2, _springParticle);
//	_force_generators.push_back(_spring); _force_generators.push_back(f2);
//	_particles.push_back(p1); _particles.push_back(_springParticle);
//}
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