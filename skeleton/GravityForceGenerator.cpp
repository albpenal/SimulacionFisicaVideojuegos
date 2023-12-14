#include "GravityForceGenerator.h"

void GravityForceGenerator::updateForce(particle* p, double t) {
	// Apply the mass scaled gravity
	p->addForce(_gravity * p->getMass());
}

void GravityForceGenerator::updateForce(RigidBody* rb, double t) {
	// Apply the mass scaled gravity
	rb->addForce(_gravity * rb->getMass());
}