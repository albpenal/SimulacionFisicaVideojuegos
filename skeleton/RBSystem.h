#pragma once
#include "core.hpp"
#include <vector>
#include <list>
#include "RigidBody.h"
#include "RigidBodyGenerator.h"
#include "RBShoot.h"
#include "RigidBodyForceRegistry.h"
#include "GravityForceGenerator.h"
#include "ExplosionForceGenerator.h"
#include "PlatosGenerator.h"
#include "WindForceGenerator.h"

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
	RBShoot* RBS;
	PlatosGenerator* ptG;
	RigidBodyForceRegistry forceRegistry;
	list<ForceGenerator*> forceGenerators;


public:
	RBSystem(PxScene* scenes, PxPhysics* gPhysics);
	void update(double t);
	void deleteUnusedRB();
	void addRBS(list<RigidBody*> lrb);
	void addRBS(RigidBody* rb);
	void createGenerators(bool cubo);

	void applyGravity(Vector3 grav) {
		GravityForceGenerator* g = new GravityForceGenerator(grav);
		for (auto rb : rbs)
			forceRegistry.addRegistry(g, rb);
	}

	void applyGravityToPlate(Vector3 grav, RigidBody* rig) {
		GravityForceGenerator* g = new GravityForceGenerator(grav);
		forceRegistry.addRegistry(g, rig);
	}
	
	void applyWindToPlate(Vector3 wind, RigidBody* rig) {
		WindForceGenerator* w = new WindForceGenerator(wind);
		forceRegistry.addRegistry(w, rig);
	}

	void applyExplosion() {
		ExplosionForceGenerator* e = new ExplosionForceGenerator(10000, 500, 2);
		for (auto rb : rbs)
			forceRegistry.addRegistry(e, rb);
	}

	RBShoot* GetRBShoot() { return RBS; }
	PlatosGenerator* GetPlatos() { return ptG; }
};

// aplicar alguna fuerxa a sr