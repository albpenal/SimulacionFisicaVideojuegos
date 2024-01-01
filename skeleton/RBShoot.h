#pragma once
#include <list>
#include <random>
#include <iostream>
#include "RigidBody.h"
using namespace std;

class RBShoot
{
	private:
		PxScene* scene;
		PxPhysics* physics;

		int nGen;
		Vector3 pos, vel;

		float timeUntilNextGeneration;

		bool shoot;
		RigidBody* RB;
	public:
		RBShoot(PxScene* Scene, PxPhysics* Physics, Vector3 Pos);
		void update(float t);
		bool generate();
		RigidBody* getRB() { return RB; }

		bool Shoot(Vector3 velo) { shoot = true; vel = velo;  return generate(); }

};

