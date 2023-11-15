#include "WindForceGenerator.h"
WindForceGenerator::WindForceGenerator(const Vector3& w, const float k1, const float k2)
    : DragGenerator(k1, k2), wind(w) {}

void WindForceGenerator::updateForce(particle* particle, double t) {
    Vector3 v = particle->getVel();
    Vector3 windForce = _k1 * (wind - v); // Simplificada a solo fuerza lineal
    particle->addForce(windForce);
}