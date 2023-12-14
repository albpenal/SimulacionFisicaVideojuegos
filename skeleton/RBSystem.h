#pragma once
#include "core.hpp"
#include <vector>
#include <list>
#include "RigidBody.h"
#include "RigidBodyGenerator.h"
#include "RigidBodyForceRegistry.h"
#include "GravityForceGenerator.h"
#include "ExplosionForceGenerator.h"

using namespace std;

const int MAXRBS = 200;

class RBSystem {
protected:
	PxScene* scene;
	PxPhysics* physics;
	Camera* camera;
	int numRB;
	list<RigidBody*> rbs;
	list<RigidBody*> rbsToDelete;
	vector<RigidBodyGenerator*> rbGenerators;

	RigidBodyForceRegistry forceRegistry;
	list<ForceGenerator*> forceGenerators;

public:
	RBSystem(PxScene* scenes, PxPhysics* gPhysics);
	void update(double t);
	void deleteUnusedRB();
	void addRBS(list<RigidBody*> lrb);

	void createGenerators(bool cubo);

	void applyGravity(Vector3 grav) {
		GravityForceGenerator* g = new GravityForceGenerator(grav);
		for (auto rb : rbs)
			forceRegistry.addRegistry(g, rb);
	}
	void applyExplosion() {
		ExplosionForceGenerator* e = new ExplosionForceGenerator(10000, 500, 2);
		for (auto rb : rbs)
			forceRegistry.addRegistry(e, rb);
	}
};

// aplicar alguna fuerxa a sr