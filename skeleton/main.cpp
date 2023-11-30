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

std::string display_text = "This is a test";

using namespace physx;

// Instancias globales de PhysX
PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;
PxFoundation* gFoundation = NULL;
PxPhysics* gPhysics = NULL;
PxMaterial* gMaterial = NULL;
PxPvd* gPvd = NULL;

ParticleGenerator* partGen;
list<particle*> particles;
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
    
    partGen = new ParticleGenerator();

    

    
    PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
    sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
    gDispatcher = PxDefaultCpuDispatcherCreate(2);
    sceneDesc.cpuDispatcher = gDispatcher;
    sceneDesc.filterShader = contactReportFilterShader;
    sceneDesc.simulationEventCallback = &gContactReportCallback;
    gScene = gPhysics->createScene(sceneDesc);
}

// Función para configurar lo que sucede en cada paso de la física
void stepPhysics(bool interactive, double t)
{
    PX_UNUSED(interactive);
    partGen->update(t);
    //pt->update(t);
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
    gScene->simulate(t);
    gScene->fetchResults(true);
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
    //delete pt;
    for (auto& i : particles) delete i;
    particles.clear();
    gFoundation->release();
}

// Función llamada cuando se presiona una tecla
void keyPress(unsigned char key, const PxTransform& camera)
{
    PX_UNUSED(camera);

    switch (toupper(key))
    {
    case 'F': // FIREBALL
    {
        Camera* camera = GetCamera();
        double damp = 0.9f;
        float vel = 10.0f;
        Vector4 color = Vector4(1, 0, 0, 1);
        float r = 0.1f;
        particle* p = new particle(camera->getTransform(), camera->getDir() * vel, Vector3 (0,0,0), Vector3(0, -0.6, 0), 1.0f, damp, color, r);
        particles.push_back(p);
        break;
    }
    case 'Z':
    {
        Camera* camera = GetCamera();
        PxTransform tr = camera->getTransform();
        tr.p.z -= 10;
        tr.p.x -= 10;
        tr.p.y -= 10;
        partGen->generateFirework(tr, Vector3(0, 8, 0), Vector3(0, 0, 0), Vector3(0, 0, 0), 1.0f, 0.9f, Vector4(0.3, 0.3, 1, 1), 0.8f, 3);
        break;
    }
    case '1':
    {
        partGen->getS()->applyGravity(Vector3(0, -9.8, 0));
        break;
    }
    case '2':
    {
        partGen->getS()->applyWind(Vector3(-8, 0, -7));
        break;
    }
    case '3':
    {
        partGen->getS()->applyVortex(Vector3(-10, 0, 0));
        break;
    }
    case '4':
    {
        partGen->getS()->applyExplosion();
        break;
    }
    case 'C':
    {
        partGen->getS()->deleteAllParticles();
        break;
    }
    case 'K':
    {
        partGen->getS()->changeK(5);
        break;
    }
    case '0':
    {
        partGen->getS()->generateSpringDemo(ParticleSystem::NORMAL);
        break;
    }
    case '9':
    {
        partGen->getS()->generateSpringDemo(ParticleSystem::STATIC);
        break;
    }
    case '8':
    {
        partGen->getS()->generateSpringDemo(ParticleSystem::SLINKY);
        break;
    }
    case '7':
    {
        partGen->getS()->generateBuoyancy();
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
