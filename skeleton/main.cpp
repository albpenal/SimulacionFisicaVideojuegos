#include <ctype.h>
#include <PxPhysicsAPI.h>
#include <vector>
#include <iostream>
#include <list>
#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "particle.h"
#include "ParticleGenerator.h"
using namespace std;

std::string start = "PRESS 'ENTER' TO PLAY";
std::string howtoplay = "AIM AND SHOOT THE SHAPES WITH THE LEFT CLICK";
int game = 0;
float gameTime = 20.0f;
int gameScore = 0;
using namespace physx;

// Instancias globales de PhysX
const float WIN = 512.0f;
PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;
PxFoundation* gFoundation = NULL;
PxPhysics* gPhysics = NULL;
PxMaterial* gMaterial = NULL;
PxPvd* gPvd = NULL;
ParticleGenerator* partGen;
//particle* pt;
PxDefaultCpuDispatcher* gDispatcher = NULL;
PxScene* gScene = NULL;
ContactReportCallback gContactReportCallback;



// Inicializar el motor de física
void initPhysics(bool interactive)
{
    PX_UNUSED(interactive);

    gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

    gPvd = PxCreatePvd(*gFoundation);
    PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
    gPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

    gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true, gPvd);

    gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

    //pt = new particle(PxTransform(Vector3(-20, 20, 10)), Vector3(0, 20.5, 0), Vector3(0, -9.8, 0), 1.0f, 1.0f, Vector4(0.5, 1.0, 0.2, 1), 10.0f);
    

    PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
    sceneDesc.gravity = PxVec3(0.0f, 0.0f, 0.0f);
    gDispatcher = PxDefaultCpuDispatcherCreate(2);
    sceneDesc.cpuDispatcher = gDispatcher;
    sceneDesc.filterShader = contactReportFilterShader;
    sceneDesc.simulationEventCallback = &gContactReportCallback;
    gScene = gPhysics->createScene(sceneDesc);

    partGen = new ParticleGenerator(gScene, gPhysics);
}

// Función para configurar lo que sucede en cada paso de la física
void stepPhysics(bool interactive, double t)
{
    PX_UNUSED(interactive);
    partGen->update(t);
    gScene->simulate(t);
    gScene->fetchResults(true);
    if (game == 1) gameTime -= t;
    if (gameTime <= 0 && game != 2) {
        partGen->setGameState(2);
    }
        
}

// Función para limpiar datos
void cleanupPhysics(bool interactive)
{
    PX_UNUSED(interactive);

    gScene->release();
    gDispatcher->release();
    gPhysics->release();
    PxPvdTransport* transport = gPvd->getTransport();
    gPvd->release();
    transport->release();
    gFoundation->release();
    delete partGen;
}

void mousePress(int button, int state, int x, int y) {
    if (partGen->getGameState() == 1 && button == 0 && state == 0) {
        Camera* camera = GetCamera();
        Vector3 dire = Vector3((min(WIN, x) - WIN / 2) / WIN, -((min(WIN, y) - WIN / 2) / WIN), -1).getNormalized();
        float vel = 100.0f;
        if(partGen->getRB()->GetRBShoot()->Shoot(dire * vel)) partGen->getRB()->addRBS(partGen->getRB()->GetRBShoot()->getRB());
    }
}

// Función llamada cuando se presiona una tecla
void keyPress(unsigned char key, const PxTransform& camera)
{
    PX_UNUSED(camera);

    switch (toupper(key))
    {
    case '\r':
    {
        partGen->setGameState(1);
        break;
    }
    default:
        break;
    }
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
    PX_UNUSED(actor1);
    PX_UNUSED(actor2);

    // Platos contra paredeso suelos
    if ((actor1->getName() == "PLATO" && actor2->getName() == "SUELO")) {
        RigidBody* rb = static_cast<RigidBody*>(actor1->userData);
        rb->setAlive(false);
    }
    else if ((actor2->getName() == "PLATO" && actor1->getName() == "SUELO")) {
        RigidBody* rb = static_cast<RigidBody*>(actor2->userData);
        rb->setAlive(false);
    }

    // Bala contra plato
    else if ((actor2->getName() == "PLATO" && actor1->getName() == "BALA")) {
        RigidBody* rb = static_cast<RigidBody*>(actor2->userData);
        RigidBody* rb2 = static_cast<RigidBody*>(actor1->userData);
        if(rb->getScore() > 0) gameScore += rb->getScore();
        rb->resetScore();
        rb->setAlive(false);
        rb2->setAlive(false);
    }
}


int main(int, const char* const*)
{
#ifndef OFFLINE_EXECUTION 
    extern void renderLoop();
    renderLoop();
#else
    const PxU32 frameCount = 100;
    initPhysics(false);
    for (PxU32 i = 0; i < frameCount; i++)
        stepPhysics(false);
    cleanupPhysics(false);
#endif

    return 0;
}
