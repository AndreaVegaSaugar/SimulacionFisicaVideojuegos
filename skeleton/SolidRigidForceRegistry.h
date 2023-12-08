#pragma once
#include <map>
#include "SolidRigidForceGenerator.h"

typedef std::pair<SolidRigidForceGenerator*, SolidRigid*> sR_FRPair;

class SolidRigidForceRegistry : public std::multimap<SolidRigidForceGenerator*, SolidRigid*> {
public:
	void updateForces(double duration) {
		for (auto it = begin(); it != end(); ++it) {
			if (it->second->alive) it->first->updateForce(it->second, duration);
		}
	}

	void addRegistry(SolidRigidForceGenerator* fg, SolidRigid* p) {
		insert(sR_FRPair(fg, p));
	}

	void addParticleListRegistry(std::list<SolidRigid*> p, std::list<SolidRigidForceGenerator*> l) {
		for (auto it = l.begin(); it != l.end(); ++it) {
			for (SolidRigid* part : p) {
				addRegistry((*it), part);
			}
		}
	}
	void addParticleListRegistrySingleGen(std::list<SolidRigid*> p, SolidRigidForceGenerator* l) {
		for (SolidRigid* part : p) {
			addRegistry(l, part);
		}
	}

	void deleteGeneratorRegistry(SolidRigidForceGenerator* f) {
		//erase(it);
		for (auto it = begin(); it != end();) {
			if (it->first == f) {
				it = erase(it);
				//std::cout << "borrado mapa" << std::endl;
			}
			else ++it;
		}

	}

	void deleteParticleRegistry(SolidRigid* p) {
		for (auto it = begin(); it != end();) {
			auto ot = it++;
			if (ot->second == p)
				erase(ot);
		}
	}
};