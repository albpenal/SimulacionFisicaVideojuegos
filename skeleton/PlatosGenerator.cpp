#include "PlatosGenerator.h"

PlatosGenerator::PlatosGenerator(PxScene* Scene, PxPhysics* Physics, Vector3 Pos) {
	scene = Scene;
	physics = Physics;
	pos = Pos;
	pos.z = -40;
	timeUntilNextGeneration = 0.0f;
	vel = Vector3(0, 0, 0);
}

void PlatosGenerator::update(float t) {
	timeUntilNextGeneration -= t;
}

bool PlatosGenerator::generate() {
	if (timeUntilNextGeneration <= 0) { // Si debe generar (tiempo y activo)
		RB = newPlato();
		timeUntilNextGeneration = 1.2f; // Actualiza el tiempo hasta la generación
		return true;
	}
	else return false;
}

RigidBody* PlatosGenerator::newPlato() {
	RigidBody* rb;
	int dire = rand() % 2;
	if (dire == 0) { // horizontal
		int iz = rand() % 2;
		if (iz == 0) { // izquierda
			int lugar = rand() % 3;
			pos.x -= 20;
			pos.z += 4;
			if (lugar == 0) { // arriba
				pos.y += 20;
			}
			else if (lugar == 1) { // centro 

			}
			else { // abajo
				pos.y -= 20;
			}
		}
		else { // derecha
			int lugar = rand() % 3;
			pos.x += 20;
			pos.z += 1;
			if (lugar == 0) { // arriba
				pos.y += 20;
			}
			else if (lugar == 1) { // centro 

			}
			else { // abajo
				pos.y -= 20;
			}
		}
		rb = new RigidBody(scene, physics, pos, vel, Vector3(1, 2, 3), 3, 5, s_cube, Vector4(0, 0, 1, 1), "PLATO", 3, 10);
	}
	else { // vertical
		int arr = rand() % 2;
		if (arr == 0) { // arriba
			int lugar = rand() % 3;
			pos.y += 20;
			pos.z -= 5;
			if (lugar == 0) { // iz
				pos.x += 20;
			}
			else if (lugar == 1) { // centro 

			}
			else { // der
				pos.x -= 20;
			}
		}
		else { // abajo
			int lugar = rand() % 3;
			pos.y -= 20;
			pos.z -= 2;
			if (lugar == 0) { // iz
				pos.x += 20;
			}
			else if (lugar == 1) { // centro 

			}
			else { // dr
				pos.x -= 20;
			}
		}
		rb = new RigidBody(scene, physics, pos, vel, Vector3(1, 1, 1), 1, 5, s_sphere, Vector4(0, 1, 0, 1), "PLATO", 3, 20);
	}
	pos = { 50, 50, -40 };
	return rb;
}
