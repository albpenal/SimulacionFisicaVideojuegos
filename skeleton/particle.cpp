#include "particle.h"

void particle::update() {
	pos->p += vel;
}

particle::particle(Vector3 initpos) {
	pos = new PxTransform(Vector3(0, 0, 0));
	vel = Vector3(0, 0.1, 0);
	rend = new RenderItem(CreateShape(PxSphereGeometry(5)), pos, Vector4(1, 0, 0, 1));
}