#pragma once
#include <map>
#include "ForceGenerator.h"

typedef std::pair<ForceGenerator*, Particle*> FRPair;

class ParticleForceRegistry : public std::multimap<ForceGenerator*, Particle*> {
public:
	void updateForces(double duration) {
		for (auto it = begin(); it != end(); ++it) {
			if (it->second->alive) it->first->updateForce(it->second, duration);
		}
	}

	void addRegistry(ForceGenerator* fg, Particle* p) {
		insert(FRPair(fg, p));
	}

	void addParticleListRegistry(std::list<Particle*> p, list<ForceGenerator*> l) {
		for (auto it = l.begin(); it != l.end(); ++it) {
			for (Particle* part : p) {
				addRegistry((*it), part);
			}
		}
	}
	void addParticleListRegistrySingleGen(std::list<Particle*> p, ForceGenerator* l) {
		for (Particle* part : p) {
			addRegistry(l, part);
		}
	}

	void deleteGeneratorRegistry(ForceGenerator* f) {
		//erase(it);
		for (auto it = begin(); it != end();) {
			if (it->first == f) {
				it = erase(it);
				//std::cout << "borrado mapa" << std::endl;
			}
			else ++it;
		}

	}

	void deleteParticleRegistry(Particle* p) {
		for (auto it = begin(); it != end();) {
			auto ot = it++;
			if (ot->second == p)
				erase(ot);
		}
	}
};