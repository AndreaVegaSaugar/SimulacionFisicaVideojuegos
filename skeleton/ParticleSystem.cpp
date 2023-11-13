#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(const Vector3& g) {
	_gravity = g;
	_zone.x_Max = 500; _zone.x_Min = -500; _zone.y_Max = 500; _zone.y_Min = -500; _zone.z_Max = 500; _zone.z_Min = -500;

	//_particle_generators.push_back(new GaussianParticleGenerator("fuente", Vector3(1, 1, 1), Vector3(10, 10, 10), Vector3(0, 0, 0), Vector3(0, 30, 0), _gravity, 1));
	//_particle_generators.push_back(new UniformParticleGenerator("fuente", Vector3(1, 1, 1), Vector3(-1, -1, -1), Vector3(50, 50, 50), Vector3(-50, 10, -50), _gravity, 1));
	//_firework_generator = new FireworkGenerator();
	_particle_force_registry = new ParticleForceRegistry();
	auto gravityGen1 = new GravityForceGenerator(Vector3(0, -10, 0));
	auto gravityGen2 = new GravityForceGenerator(Vector3(0, 10, 0));
	_force_generators.push_back(gravityGen1);
	_force_generators.push_back(gravityGen2);
	for (int i = 0; i < 10; ++i) {
		auto p = new Particle(Vector3(rand() % 10, 0, rand() % 10), Vector3(0, 10, 0), Vector3(0, 0, 0), 0.998, 30, 1, 1, Vector4(255, 255, 0, 1), false);
		_particles.push_back(p);
		_particle_force_registry->addRegistry(gravityGen1, p);
		_particle_force_registry->addRegistry(gravityGen2, p);
	}
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
			auto ot = (*it)->onDeath();
			auto ut = _particles.end();
			_particles.splice(ut, ot);
			delete (*it);
			it = _particles.erase(it);
		}
	}
	for (ParticleGenerator* pG : _particle_generators) {
		auto particleList = pG->generateParticles();
		auto it = _particles.begin();
		_particles.splice(it, particleList);
	}
	_particle_force_registry->updateForces(t);
}

void ParticleSystem::generateFirework() {
	Particle* p = _firework_generator->shoot();
	_particles.push_back(p);
}

ParticleGenerator* ParticleSystem::getParticleGenerator(const string& name) {
	for (ParticleGenerator* pG : _particle_generators) {
		if (pG->getName() == name) return pG;
	}
}