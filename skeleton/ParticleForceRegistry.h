#pragma once
#include <map>
#include "ForceGenerator.h"

typedef std::pair<ForceGenerator*, Particle*> FRPair;

class ParticleForceRegistry : public std::multimap<ForceGenerator*, Particle*> {
public:
	void updateForces(double duration) {
		for (auto it = begin(); it != end(); ++it) {
			it->first->updateForce(it->second, duration);
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

	void deleteParticleRegistry(Particle* p) {
		for (auto it = begin(); it != end();) {
			auto ot = it++;
			if (ot->second == p)
				erase(ot);
		}
	}
};