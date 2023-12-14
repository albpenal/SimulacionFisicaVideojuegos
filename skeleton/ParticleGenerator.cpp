#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator(PxScene* scene, PxPhysics* gPhysics) {
    partSyst = new ParticleSystem();
    rbSys = new RBSystem(scene, gPhysics);
}

ParticleGenerator::~ParticleGenerator() {

}

void ParticleGenerator::update(float t) {
    /*cooldown += t;
    if (cooldown >= 0.01) {
        generate();
        cooldown = 0.0f;
    }*/
    partSyst->update(t);
    rbSys->update(t);
}

Vector3 ParticleGenerator::UniformDistribution(int size) {
    Vector3 rnd;
    rnd.x = rand() % size - (size / 2);
    rnd.y = rand() % size - (size / 2);
    rnd.z = rand() % size - (size / 2);
    return rnd;
}

Vector3 ParticleGenerator::NormalDistribution(float m, float d) {
    Vector3 rnd;

    // Genera n�meros aleatorios en una distribuci�n normal
    float x = RandomNormal(m, d);
    float y = RandomNormal(m, d);
    float z = RandomNormal(m, d);

    rnd.x = x;
    rnd.y = y;
    rnd.z = z;

    return rnd;
}

float ParticleGenerator::RandomNormal(float mean, float stddev) {
    // Genera un n�mero aleatorio con distribuci�n normal usando Box-Muller
    float u1 = 1.0 - rand() / static_cast<float>(RAND_MAX);
    float u2 = 1.0 - rand() / static_cast<float>(RAND_MAX);
    float z = sqrt(-2.0 * log(u1)) * cos(2.0 * 3.14 * u2);
    return mean + stddev * z;
}

void ParticleGenerator::generate() {
    Camera* camera = GetCamera();
    
    // posicion con randoms
    Vector3 rPos = UniformDistribution(20);
    //Vector3 rPos = NormalDistribution(0, 5);
    PxTransform pos = PxTransform(Vector3(camera->getTransform().p.x - 20 + rPos.x,
        camera->getTransform().p.y + rPos.y, camera->getTransform().p.z - 20 + rPos.z));

    // velocidad con randoms
    Vector3 rVel = UniformDistribution(10);
    //Vector3 rVel = NormalDistribution(5, 5);
    Vector3 vel = Vector3(camera->getDir().x + rVel.x, camera->getDir().y + rVel.y, camera->getDir().z + rVel.z);
    
    //otros par�metros
    Vector4 color;
    float r = 0.4f; // radius
    double damp = 0.9f; // damping
    Vector3 gravity = Vector3(0, 0, 0);
    Vector3 acceleration = Vector3(0, 0, 0);
    float weight = 1.0f;

    int rndgen = rand() % 1;
    if (rndgen == 0) {
        /*color = Vector4(0, 1, 0, 1);
        particle* p = new particle(pos, vel, acceleration, gravity, weight, damp, color, r);*/
        particle* p = new particle(pos);
        partSyst->addParticle(p);
    }
    else {
        r = 0.8f;
        vel = Vector3(0, 8, 0);
        gravity = Vector3(0, 0, 0);
        color = Vector4(0.3, 0.3, 1, 1);
        Firework* f = new Firework(pos, vel, acceleration, gravity, weight, damp, color, r, partSyst, this, 3);
        partSyst->addFirework(f);
    }
    
}

void ParticleGenerator::generateFirework(PxTransform pos, Vector3 vel, Vector3 acc, Vector3 grav, float weight, float damping, Vector4 c, float radius, int gen) {
    Vector3 r = UniformDistribution(5);
    Firework* f = new Firework(pos, vel + r, acc, grav, weight, damping, c, radius, partSyst, this, gen);
    partSyst->addFirework(f);
}

void ParticleGenerator::generateParticle(PxTransform pos) {
    particle* p = new particle(pos);
    partSyst->addParticle(p);
}


