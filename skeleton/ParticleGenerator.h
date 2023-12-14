#pragma once
#include "particle.h"
#include "ParticleSystem.h"
#include "RBSystem.h"
class ParticleGenerator
{
private:
	float cooldown = 1.0f;
	ParticleSystem* partSyst;
	RBSystem* rbSys;
public:
	ParticleGenerator(PxScene* scene, PxPhysics* gPhysics);
	~ParticleGenerator();
	Vector3 UniformDistribution(int size);
	Vector3 NormalDistribution(float m, float d);
	float RandomNormal(float m, float d);
	void update(float t);
	void generate();
	ParticleSystem* getS() { return partSyst; }
	RBSystem* getRB() { return rbSys; }
	void generateParticle(PxTransform pos);
	void generateFirework(PxTransform pos, Vector3 vel, Vector3 acc, Vector3 grav, float weight, float damping, Vector4 c, float radius, int gen);

};

