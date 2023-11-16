#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(const Vector3& g) {
	_gravity = g;
	_zone.x_Max = 800; _zone.x_Min = -800; _zone.y_Max = 800; _zone.y_Min = -800; _zone.z_Max = 800; _zone.z_Min = -800;

	//_particle_generators.push_back(new GaussianParticleGenerator("fuente", Vector3(1, 1, 1), Vector3(10, 10, 10), Vector3(0, 0, 0), Vector3(0, 30, 0), 1));
	//_particle_generators.push_back(new UniformParticleGenerator("fuente", Vector3(1, 1, 1), Vector3(-1, -1, -1), Vector3(50, 50, 50), Vector3(-50, 10, -50), 1));
	//_firework_generator = new FireworkGenerator();

	_particle_force_registry = new ParticleForceRegistry();

	auto gravityGen = new GravityForceGenerator(Vector3(0, -10, 0));
	_force_generators.push_back(gravityGen);

	/*auto dragGen = new ParticleDragGenerator(2, 0, Vector3(20, 0, 0));
	_force_generators.push_back(dragGen);*/

	/*auto whirlGen = new WhirlwindGenerator(1, 2, 0, Vector3(0, 20, 0));
	_force_generators.push_back(whirlGen);*/

	_particle_generators.push_back(new UniformParticleGenerator("fuente", Vector3(1, 5, 1), Vector3(-1, 5, -1), Vector3(10, 30, 10), Vector3(-10, 30, -10), 1));
}

ParticleSystem::~ParticleSystem() {
	for (auto it = _particle_generators.begin(); it != _particle_generators.end(); ++it) {
		delete (*it);
	}
	if (_firework_generator != nullptr) delete _firework_generator;
}

void ParticleSystem::update(double t) {
	
	for (auto it = _particles.begin(); it != _particles.end();) {
		if ((*it)->isAlive() && isInZone(*it)) {
			(*it)->integrate(t);
			++it;
		}
		else {
			_particle_force_registry->deleteParticleRegistry((*it));
			auto ot = (*it)->onDeath();
			auto ut = _particles.end();
			_particles.splice(ut, ot);
			delete (*it);
			it = _particles.erase(it);
		}
	}
	for (ParticleGenerator* pG : _particle_generators) {
		auto particleList = pG->generateParticles();
		_particle_force_registry->addParticleListRegistry(particleList, _force_generators); //COSA NUEVA
		auto it = _particles.begin();
		_particles.splice(it, particleList);
	}
	_particle_force_registry->updateForces(t);
}

void ParticleSystem::generateFirework() {
	Particle* p = _firework_generator->shoot();
	_particles.push_back(p);
}

void ParticleSystem::generateExplosion() {
	std::list<ForceGenerator*> aux;
	aux.push_back(new ExplosionGenerator(10000, 500, 20));
	_particle_force_registry->addParticleListRegistry(_particles, aux);
	//_force_generators.push_back(explosionGen);
}

ParticleGenerator* ParticleSystem::getParticleGenerator(const string& name) {
	for (ParticleGenerator* pG : _particle_generators) {
		if (pG->getName() == name) return pG;
	}
}