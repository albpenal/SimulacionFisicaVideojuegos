#include "SpringForceGenerator.h"

void SpringForceGenerator::updateForce(particle* particle, double t) {
	Vector3 relative_pos_vector = _other->getPos()->p - particle->getPos()->p;
	Vector3 force;

	const float lenght = relative_pos_vector.normalize();
	const float delta_x = lenght - _resting_length;

	force = relative_pos_vector * delta_x * _k;

	particle->addForce(force);
}