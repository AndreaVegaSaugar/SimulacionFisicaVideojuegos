#include "SolidRigidSystem.h"

SolidRigidSystem::SolidRigidSystem(PxScene* scene, PxPhysics* physics) {
	_zone.x_Max = 1000; _zone.x_Min = -1000; _zone.y_Max = 1000; _zone.y_Min = -50; _zone.z_Max = 1000; _zone.z_Min = -1000;
	this->scene = scene;

	_solidRigid_force_registry = new SolidRigidForceRegistry();

	_solidRigid_generators.push_back(new UniformSolidRigidGenerator(this->scene, physics, "chuloUniform", { -30, 50, 5 }, { -70, 50, -5 }, { 0.01, -10, 0.01 }, { 0.01, -20, 0.01 }, 1));
	_solidRigid_generators.push_back(new GaussianSolidRigidGenerator(this->scene, physics, "chuloGaussian", { 20, 0.01, 5 }, { 0.01, 5, 0.01 }, { 50, 50, 0.01 }, { 0.01, -15, 0.01 }, 1));

	generateTornado();
}

SolidRigidSystem::~SolidRigidSystem() {
	for (auto it = _solidRigid_generators.begin(); it != _solidRigid_generators.end(); ++it) {
		delete (*it);
	}
	for (auto it = _solidRigids.begin(); it != _solidRigids.end(); ++it) {
		delete (*it);
	}
}

void SolidRigidSystem::update(double t) {
	_solidRigid_force_registry->updateForces(t);
	for (auto it = _explosion_solidRigid_generators.begin(); it != _explosion_solidRigid_generators.end();) {
		if (!(*it)->updateTime(t)) {
			_solidRigid_force_registry->deleteGeneratorRegistry(*it);
			delete (*it);
			it = _explosion_solidRigid_generators.erase(it);
		}
		else ++it;
	}
	for (auto it = _solidRigids.begin(); it != _solidRigids.end();) {
		if ((*it)->isAlive() && isInZone(*it)) {
			(*it)->integrate(t);
			++it;
		}
		else {
			delete (*it);
			it = _solidRigids.erase(it);
		}
	}
	for (SolidRigidGenerator* pG : _solidRigid_generators) {
		pG->auxTime += t;
		if (pG->auxTime >= pG->generationTime) {
			auto solidRigidList = pG->generateSolidRigids();
			_solidRigid_force_registry->addParticleListRegistry(solidRigidList, _solidRigid_force_generators); //COSA NUEVA
			for (SolidRigid* s : solidRigidList) {
				pG->auxTime = 0;
			}
			auto it = _solidRigids.begin();
			_solidRigids.splice(it, solidRigidList);
		}
	}
}

void SolidRigidSystem::generateTornado() {
	auto whirlGen = new WhirlwindSolidRigidGenerator(6, 12, 0, Vector3(0, 120, 0));
	_solidRigid_force_generators.push_back(whirlGen);
}

void SolidRigidSystem::generateExplosion() {
	std::list<SolidRigidForceGenerator*> aux;
	auto explosionGen = new ExplosionSolidRigidGenerator(Vector3(0, 20, 0), 5, 100000000, 500, 20);
	_solidRigid_force_registry->addParticleListRegistrySingleGen(_solidRigids, explosionGen);
	_explosion_solidRigid_generators.push_back(explosionGen);
}