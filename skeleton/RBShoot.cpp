#include "RBShoot.h"

RBShoot::RBShoot(PxScene* Scene, PxPhysics* Physics, Vector3 Pos) {
	scene = Scene;
	physics = Physics;
	pos = Pos;
	shoot = false;
	timeUntilNextGeneration = 0.5f;
}

void RBShoot::update(float t) {
	timeUntilNextGeneration -= t;
}

bool RBShoot::generate() {
	if (shoot && timeUntilNextGeneration <= 0) { // Si debe generar (tiempo y activo)
		RigidBody* rb = new RigidBody(scene, physics, pos, vel, Vector3(0, 0, 0), 0.1, 5, s_sphere, Vector4(1, 0, 0, 1), "BALA", 0.5);
		RB = rb;
		shoot = false;
		timeUntilNextGeneration = 0.5f; // Actualiza el tiempo hasta la generación
		return true;
	}
	else return false;
}