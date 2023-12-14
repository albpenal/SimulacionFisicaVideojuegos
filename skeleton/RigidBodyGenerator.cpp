#include "RigidBodyGenerator.h"

RigidBodyGenerator::RigidBodyGenerator(PxScene* Scene, PxPhysics* Physics, RigidBody* rb, Vector3 Pos, Vector3 Vel, int numGen, float Frecuency) {
	scene = Scene;
	physics = Physics;
	model = rb;
	pos = Pos; vel = Vel;
	nGen = numGen;
	active = true;
	frecuency = Frecuency;
	timeUntilNextGeneration = frecuency;
}

void RigidBodyGenerator::update(float t) {
	timeUntilNextGeneration -= t;
}

list<RigidBody*> RigidBodyGenerator::generateBodies(){
	list<RigidBody*> listRB;
	if (model != nullptr) {
		if (active && timeUntilNextGeneration <= 0) { // Si debe generar (tiempo y activo)
			for (int i = 0; i < nGen; i++) {
				Vector3 posicion = pos + Vector3(rand() % 4 - 2, rand() % 4 - 2, rand() % 4 - 2);
				Vector3 velocidad = vel + Vector3(rand() % 4 - 2, rand() % 4 - 2, rand() % 4 - 2);

				RigidBody* rb = new RigidBody(scene, physics, posicion, velocidad, Vector3(0, 0, 0), model->getMass(), model->getLifeTime(), model->getShape(), model->getColor());

				listRB.push_back(rb);
			}
			timeUntilNextGeneration = frecuency; // Actualiza el tiempo hasta la generación
		}
	}
	return listRB;
}