#include "gameobject.h"

#ifndef BULLETOBJECT_H
#define BULLETOBJECT_H

class BulletObject : public GameObject {
public:
    BulletObject(glm::vec3 pos,
        glm::vec3 rot,
        glm::vec3 scale,
        string modelName,
        dWorldID w,
        dSpaceID s);

    virtual void update() override;
    virtual void draw() override;

    float maxSpeed = 5;
    float maxAccel = 5;

    float spawnTime = 0;
    float despawnSeconds = 8;

    glm::vec3 targetVelocity{};
};

#endif // BULLETOBJECT_H
