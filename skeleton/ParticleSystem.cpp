#include "ParticleSystem.h"

ParticleSystem::ParticleSystem() {
    forceRegistry = new ParticleForceRegistry();
}

ParticleSystem::~ParticleSystem() {
    for (auto& i : particles) delete i;
}

void ParticleSystem::update(float t) {
    PartUpdate(t);
    FireUpdate(t);
    forceRegistry->updateForces(t);
}

void ParticleSystem::PartUpdate(float t) {
    auto it = particles.begin();
    while (it != particles.end()) {
        auto aux = it;
        ++aux;
        if ((*it)->getDestroyed()) {
            delete* it;
            particles.erase(it);
        }
        else (*it)->update(t);
        it = aux;
    }
}

void ParticleSystem::FireUpdate(float t) {
    auto it = fireworks.begin();
    while (it != fireworks.end()) {
        auto aux = it;
        ++aux;
        if ((*it)->getDestroyed()) {
            delete* it;
            fireworks.erase(it);
        }
        else (*it)->update(t);
        it = aux;
    }
}

void ParticleSystem::addParticle(particle* p) {
    particles.push_back(p);
}

void ParticleSystem::addFirework(Firework* f) {
    fireworks.push_back(f);
}

void ParticleSystem::applyGravity(Vector3 g) {
    for (auto& part : particles) {
        Vector3 grav = g; // Real gravity
        GravityForceGenerator* gravity = new GravityForceGenerator(grav);
        forceRegistry->addRegistry(gravity, part);
    }
}

void ParticleSystem::applyWind(Vector3 w) {
    for (auto& part : particles) {
        Vector3 windDirection = w; // Wind direction and strength
        float airFrictionCoefficient = 0.25, secondaryCoefficient = 0.1;
        WindForceGenerator* wind = new WindForceGenerator(windDirection, airFrictionCoefficient, secondaryCoefficient);
        forceRegistry->addRegistry(wind, part);
    }
}

void ParticleSystem::applyVortex(Vector3 vort) {
    for (auto& part : particles) {
        Vector3 vortexBaseWind = Vector3(-10, 0, 0); // Base wind direction and strength for the vortex
        float vortexForceConstant = 0.01; // Vortex force constant
        VortexForceGenerator* vortex = new VortexForceGenerator(vortexForceConstant, vortexBaseWind);
        forceRegistry->addRegistry(vortex, part);
    }
}

void ParticleSystem::applyExplosion() {
    for (auto& part : particles) {
        float explosionForceConstant = 1000; // Explosion force constant
        float range = 1500; // Range of the burst effect
        float duration = 2; // Duration of the effect
        ExplosionForceGenerator* expl = new ExplosionForceGenerator(explosionForceConstant, range, duration);
        forceRegistry->addRegistry(expl, part);
    }
}

void ParticleSystem::deleteAllParticles() {
    // Iterate through the particle list and delete each particle
    for (auto& part : particles) {
        forceRegistry->deleteParticleRegistry(part); // Remove the particle from the force registry
        delete part; // Delete the particle
    }

    // Clear the list after deleting all particles
    particles.clear();
}