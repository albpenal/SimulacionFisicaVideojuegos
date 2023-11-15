#include "VortexForceGenerator.h"

void VortexForceGenerator::updateForce(particle* p, double t) {
	Camera* camera = GetCamera();

	Vector3 c = Vector3(camera->getTransform().p.x + 50, camera->getTransform().p.y - 50, camera->getTransform().p.z - 50);

	Vector3 pos = p->getPos()->p;
	Vector3 vortexForce = K * calc(c, pos);
	p->addForce(vortexForce);
}

Vector3 VortexForceGenerator::calc(Vector3 c, Vector3 p) {
	//menos k = menos v del torbellino
	const float K = 2.0f;

	//Calcula la dirección tangencial del viento
	Vector3 direction = Vector3(-(p.z - c.z), 50 - (p.y - c.y), p.x - c.x);

	//Ajusta la fuerza del viento en base a la distancia del centro
	return K * direction;
}
