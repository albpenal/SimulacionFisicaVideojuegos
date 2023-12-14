#include "RBSystem.h"


RBSystem::RBSystem(PxScene* scenes, PxPhysics* gPhysics) {
	scene = scenes;
	physics = gPhysics;
	numRB = 0;
	forceRegistry = RigidBodyForceRegistry();
	camera = GetCamera();
}

void RBSystem::update(double t) {
	//Generar
	for (RigidBodyGenerator* g : rbGenerators) { //Generadores de partículas
		addRBS(g->generateBodies());
		g->update(t);
	}
	
	forceRegistry.updateForces(t); // Actualiza las fuerzas ejercidas sobre los RB

	for (RigidBody* rb : rbs) { // RB
		if (rb->isAlive()) { rb->integrate(t); }
		else { rbsToDelete.push_back(rb); }
	}

	deleteUnusedRB();
}

void RBSystem::deleteUnusedRB() {
	for (auto it = rbsToDelete.begin(); it != rbsToDelete.end();) {
		forceRegistry.deleteRigidBodyRegistry(*it);
		rbs.remove(*it);
		delete(*it);
		it = rbsToDelete.erase(it);
		numRB--;
	}
}

void RBSystem::addRBS(list<RigidBody*> lrb) {
	for (RigidBody* r : lrb) {
		if (rbs.size() < MAXRBS) {
			rbs.push_back(r);
			numRB++;
			for (auto fg : forceGenerators) // Añade las particulas al registro de fuerzas 
				forceRegistry.addRegistry(fg, r);
		}
		else {
			delete r;
		}
	}
}

void RBSystem::createGenerators(bool cubo) {
	Vector3 pos = camera->getEye() + camera->getDir() * 50;
	Vector3 perpendicular = Vector3(0, 1, 0).cross(camera->getDir());
	if(!cubo) {
		RigidBody* model = new RigidBody(scene, physics, Vector3(0, -500, 0), Vector3(0, 0, 0), Vector3(0, 0, 0), 1, 10, s_sphere, Vector4(0.7, 0.2, 0.8, 1));
		rbGenerators.push_back(new RigidBodyGenerator(scene, physics, model, pos, Vector3(0, 0, 0), 1, 0.5));
	}
	else {
		RigidBody* model = new RigidBody(scene, physics, Vector3(0, -500, 0), Vector3(0, 0, 0), Vector3(0, 0, 0), 10, 10, s_cube, Vector4(0.8, 0.6, 0.2, 1));
		rbGenerators.push_back(new RigidBodyGenerator(scene, physics, model, pos, Vector3(0, 0, 0), 1, 0.5));
	}
}

