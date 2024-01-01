#pragma once
#include <map>
#include "ForceGenerator.h"
#include "GravityForceGenerator.h"
using namespace std;

typedef pair<ForceGenerator*, particle*> FRPair;
class ParticleForceRegistry :
    public multimap<ForceGenerator*, particle*>
{
public:
    void updateForces(double duration) {
        for (auto it = begin(); it != end(); it++)
            it->first->updateForce(it->second, duration);
    }
    void addRegistry(ForceGenerator* fg, particle* p)
    {
        FRPair pair = { fg, p };
        insert(pair);
    }
    void deleteParticleRegistry(particle* p)
    {
        for (auto it = begin(); it != end(); it++) {
            if (it->second == p) { erase(it); return; }
        }
    }



};

