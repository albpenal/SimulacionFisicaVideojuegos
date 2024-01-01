#pragma once
#include <list>
#include <random>
#include <iostream>
#include "RigidBody.h"
using namespace std;

class PlatosGenerator
{
private:
	PxScene* scene;
	PxPhysics* physics;

	int nGen;
	int score;
	Vector3 pos, vel;

	float timeUntilNextGeneration;

	RigidBody* RB;
public:
	PlatosGenerator(PxScene* Scene, PxPhysics* Physics, Vector3 Pos);
	void update(float t);
	bool generate();
	RigidBody* newPlato();
	RigidBody* getRB() { return RB; }

};

