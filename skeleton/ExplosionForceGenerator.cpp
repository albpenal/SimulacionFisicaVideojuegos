#include "ExplosionForceGenerator.h"
#include <cmath>

// Function to rotate a vector based on time
Vector3 rotateDirection(const Vector3& direction, double t) {
    // Simple rotation: rotate around the z-axis based on time
    float angle = t; // Rotate by 't' radians (adjust as needed)
    float cosAngle = cos(angle);
    float sinAngle = sin(angle);

    // Assuming z-axis rotation
    return Vector3(
        direction.x * cosAngle - direction.y * sinAngle,
        direction.x * sinAngle + direction.y * cosAngle,
        direction.z
    );
}

void ExplosionForceGenerator::updateForce(particle* p, double t) {
    Camera* camera = GetCamera();
    Vector3 explosionCenter = Vector3(camera->getTransform().p.x - 20, camera->getTransform().p.y, camera->getTransform().p.z - 20);
    Vector3 particlePosition = p->getPos()->p;

    float distance = calculateDistance(explosionCenter, particlePosition);
    if (distance <= radius) {
        Vector3 direction = (particlePosition - explosionCenter).getNormalized();
        // Rotate the direction vector over time
        direction = rotateDirection(direction, t);

        float forceIncreaseFactor = 1.0f + t * t;
        float forceMagnitude = intensity * forceIncreaseFactor / (distance * distance + 1);
        Vector3 burstForce = direction * forceMagnitude;
        p->addForce(burstForce);
    }
}

float ExplosionForceGenerator::calculateDistance(Vector3 center, Vector3 position) {
    return sqrtf(pow(position.x - center.x, 2) + pow(position.y - center.y, 2) + pow(position.z - center.z, 2));
}
