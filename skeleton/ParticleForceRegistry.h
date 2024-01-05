#pragma once
#include <map>
#include "ForceGenerator.h"

typedef std::pair<ForceGenerator*, Entity*> FRPair;

class ParticleForceRegistry : public std::multimap<ForceGenerator*, Entity*> {
public:
	void updateForces(double duration) {
		for (auto it = begin(); it != end(); ++it) {
			if (it->second->alive) it->first->updateForce(it->second, duration);
		}
	}

	void addRegistry(ForceGenerator* fg, Entity* p) {
		insert(FRPair(fg, p));
	}

	void addParticleListRegistry(std::list<Entity*> p, list<ForceGenerator*> l) {
		for (auto it = l.begin(); it != l.end(); ++it) {
			for (Entity* part : p) {
				addRegistry((*it), part);
			}
		}
	}
	void addParticleListRegistrySingleGen(std::list<Entity*> p, ForceGenerator* l) {
		for (Entity* part : p) {
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

	void deleteParticleRegistry(Entity* p) {
		for (auto it = begin(); it != end();) {
			auto ot = it++;
			if (ot->second == p)
				erase(ot);
		}
	}
};