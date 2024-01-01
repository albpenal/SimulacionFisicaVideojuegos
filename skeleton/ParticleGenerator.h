#pragma once
#include "particle.h"
#include "ParticleSystem.h"
#include "RBSystem.h"
extern int game;

class ParticleGenerator
{
private:
	float cooldown = 0.0f;
	ParticleSystem* partSyst;
	RBSystem* rbSys;
	PxScene* scene;
	PxPhysics* gPhysics;
public:
	ParticleGenerator(PxScene* sc, PxPhysics* gPh);
	~ParticleGenerator();
	Vector3 UniformDistribution(int size);
	Vector3 NormalDistribution(float m, float d);
	float RandomNormal(float m, float d);
	void initScene();
	void update(float t);
	void generate();
	ParticleSystem* getS() { return partSyst; }
	RBSystem* getRB() { return rbSys; }
	void generateParticle(PxTransform pos);
	void generateFirework(PxTransform pos, Vector3 vel, Vector3 acc, Vector3 grav, float weight, float damping, Vector4 c, float radius, int gen);
	void setGameState(int n) { 
		game = n; 
		if (game == 1) {
			partSyst->deleteAllParticles();
			partSyst->deleteAllParticles();
			initScene();
		}
		if (game == 2) {
			Camera* camera = GetCamera();
			camera->setPos({ 50,50, -300 });
			partSyst->generateSpringDemo(ParticleSystem::NORMAL);
		}
	}
	int getGameState() { return game; }

};

