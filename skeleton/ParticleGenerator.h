#pragma once
#include "particle.h"
#include "ParticleSystem.h"
class ParticleGenerator
{
private:
	float cooldown = 1.0f;
	ParticleSystem* partSyst;
public:
	ParticleGenerator();
	~ParticleGenerator();
	Vector3 UniformDistribution(int size);
	Vector3 NormalDistribution(float m, float d);
	float RandomNormal(float m, float d);
	void update(float t);
	void generate();
	ParticleSystem* getS() { return partSyst; }
	void generateParticle(PxTransform pos);
	void generateFirework(PxTransform pos, Vector3 vel, Vector3 acc, Vector3 grav, float weight, float damping, Vector4 c, float radius, int gen);

};

