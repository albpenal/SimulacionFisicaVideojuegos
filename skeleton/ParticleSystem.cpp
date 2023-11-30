#include "ParticleSystem.h"


ParticleSystem::ParticleSystem() {
    forceRegistry = new ParticleForceRegistry();
}

ParticleSystem::~ParticleSystem() {
    for (auto& i : particles) delete i;
}

void ParticleSystem::update(float t) {
    forceRegistry->updateForces(t);
    PartUpdate(t);
    FireUpdate(t);
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

void ParticleSystem::generateSpringDemo(SPRING type) {
    
    Vector3 null = Vector3(0, 0, 0);
    switch (type)
    {
    case ParticleSystem::NORMAL: {

        particle* p1 = new particle(PxTransform(10, 30, 20), null, null, null, 2, 0.9, Vector4(0.9, 0.6, 0.6, 1), 0.6);
        addParticle(p1);
        particle* p2 = new particle(PxTransform(20, 30, 10), null, null, null, 2, 0.9, Vector4(0.6, 0.6, 0.9, 1), 0.6);
        addParticle(p2);

        //ultimo booleano true = goma elastica, false = muelle
        SpringForceGenerator* f1 = new SpringForceGenerator(4, 10, p2);
        forceRegistry->addRegistry(f1, p1);
        SpringForceGenerator* f2 = new SpringForceGenerator(4, 10, p1);
        forceRegistry->addRegistry(f2, p2);
        /*GravityForceGenerator* gravity = new GravityForceGenerator(Vector3(0, -2, 0));
        forceRegistry->addRegistry(gravity, p1);*/


        break;
    }
    case ParticleSystem::STATIC: {

        // muelle con bloque fijo
        particle* p3 = new particle(PxTransform(10, 60, 20), null, null, null, 2, 0.9, Vector4(0.6, 0.9, 0.6, 1), 0.6);
        addParticle(p3);
        GravityForceGenerator* gravity = new GravityForceGenerator(Vector3(0, -9.8, 0));
        forceRegistry->addRegistry(gravity, p3);
        f3 = new AnchoredSpring(0, 10, Vector3(20, 60, 10));
        addParticle(f3->getOther());
        forceRegistry->addRegistry(f3, p3);

        break;
    }
    case ParticleSystem::SLINKY: {

        int SLINKY_SIZE = 7; float BETWEEN_SIZE = 15;

        particle* prev = new particle(PxTransform(0, 30, 10), null, null, null, 2, 0.9, Vector4(0.6, 0.9, 0.6, 1), 0.6);
        addParticle(prev);

        for (int i = 0; i < SLINKY_SIZE - 1; ++i) {
            particle* p = new particle(PxTransform(0, 30 + BETWEEN_SIZE * i, 10), null, null, null, 2, 0.9, Vector4(0.6, 0.9, 0.6, 1), 0.6);
            addParticle(p);
            SpringForceGenerator* sf = new SpringForceGenerator(15, 20, p);
            forceRegistry->addRegistry(sf, prev);
            /*GravityForceGenerator* gravity = new GravityForceGenerator(Vector3(0, -9.8, 0));
            forceRegistry->addRegistry(gravity, p);*/
            sf = new SpringForceGenerator(15, 20, prev);
            forceRegistry->addRegistry(sf, p);

            prev = p;
        }

        break;
    }
    default:
        break;
    }
}

void ParticleSystem::changeK(int k) {
    f3->setK(k);
}

void ParticleSystem::generateBuoyancy() {
    Vector3 null = Vector3(0, 0, 0);
    BuoyancyForceGenerator* water = new BuoyancyForceGenerator(6, 0.5, 1000);
    particle* p1 = new particle(PxTransform(0, 0, 0), null, null, null, 300, 0.9, Vector4(1, 0, 0, 1), 0.6, true);
    addParticle(p1);
    forceRegistry->addRegistry(water, p1);

    particle* p2 = new particle(PxTransform(10, 0, 0), null, null, null, 30000, 0.9, Vector4(1, 1, 0, 1), 0.6, true);
    addParticle(p2);
    forceRegistry->addRegistry(water, p2);

    particle* p3 = new particle(PxTransform(20, 0, 0), null, null, null, 20, 0.9, Vector4(0, 1, 0, 1), 0.6, true);
    addParticle(p3);
    forceRegistry->addRegistry(water, p3);

    particle* p4 = new particle(PxTransform(30, 0, 0), null, null, null, 120, 0.9, Vector4(0, 1, 1, 1), 0.6, true);
    addParticle(p4);
    forceRegistry->addRegistry(water, p4);
}