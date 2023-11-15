#include "GravityForceGenerator.h"

void GravityForceGenerator::updateForce(particle* p, double t) {
	// Apply the mass scaled gravity
	p->addForce(_gravity * p->getMass());
}