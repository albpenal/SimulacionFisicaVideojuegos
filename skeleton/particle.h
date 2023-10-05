#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"
#include "geometry/PxGeometry.h"
using namespace physx;
#pragma once
class particle
{
private:
	PxTransform* pos;
	Vector3 vel;
	RenderItem* rend;
public:
	particle(Vector3 initpos);
	~particle();
	void update();
};

