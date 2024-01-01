#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"
#include "PxRigidBody.h"
#include "PxShape.h"
#include <PxPhysicsAPI.h>
#include <PxPhysics.h>
#include <string>
using namespace physx;

enum Shape{s_cube, s_sphere};

class RigidBody {
protected:
	PxTransform transform;
	PxRigidDynamic* solid;
	PxShape* shape;
	RenderItem* render;

	Shape shapeType;
	float lifeTime;
	bool alive;
	int scoretoAdd;

public:
	RigidBody(PxScene* scene, PxPhysics* physics,
		const Vector3& Position, const Vector3& Velocity = Vector3(0, 0, 0), const Vector3& Inertia = Vector3(0, 0, 0),
		double Mass = 1, double LifeTime = 30,
		Shape Shape = s_cube, Vector4 Color = Vector4(0, 0, 0, 1), const char* name = "NONE", float size = 1, int score = 0) {

		scoretoAdd = score;
		transform = physx::PxTransform(Position.x, Position.y, Position.z);
		solid = physics->createRigidDynamic(transform);
		solid->setName(name);
		solid->userData = this;
		solid->setLinearVelocity(Velocity);
		solid->setAngularVelocity(Vector3(0,0,0));
		solid->setLinearDamping(0.0);
		solid->setMassSpaceInertiaTensor(Inertia);
		solid->setGlobalPose(transform);
		solid->setMass(Mass);

		lifeTime = LifeTime;
		alive = true;
		shapeType = Shape;
		
		switch (shapeType)
		{
		case s_sphere:
			shape = CreateShape(PxSphereGeometry(size));
			break;
		case s_cube:
			shape = CreateShape(PxBoxGeometry(size, size, size));
			break;
		}

		solid->attachShape(*shape);

		PxRigidBodyExt::updateMassAndInertia(*solid, 0.15);
		scene->addActor(*solid);
		render = new RenderItem(shape, solid, Color);
	}

	~RigidBody(){
		DeregisterRenderItem(render);
	}

	void integrate(float t) {
		lifeTime -= t;
		if (lifeTime <= 0 || transform.p.y <= -500) setAlive(false);
	};

	PxRigidDynamic* getRigidDynamic() { return solid; }
	Vector3 getPosition() { return solid->getGlobalPose().p; }
	PxTransform getTransform() { return solid->getGlobalPose(); }
	Vector3 getLinearVelocity() { return solid->getLinearVelocity(); }
	float getMass() { return solid->getMass(); }
	float getInvMass() { return solid->getInvMass(); }
	double getLifeTime() { return lifeTime; }
	bool isAlive() { return alive; }
	Vector4 getColor() { return render->color; }
	Shape getShape() { return shapeType; }
	int getScore() { return scoretoAdd; }
	void resetScore() { scoretoAdd = 0; }
	void setPosition(Vector3 Pos) {
		transform = PxTransform(Pos);
		solid->setGlobalPose(transform);
	}
	void setLinearVelocity(Vector3 Vel) { solid->setLinearVelocity(Vel); }
	void addForce(Vector3 F) { solid->addForce(F); }
	void setAlive(bool A = false) { alive = A; }
};
