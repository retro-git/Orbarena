#include "gameobject.h"

#ifndef ENEMYBULLETOBJECT_H
#define ENEMYBULLETOBJECT_H

class EnemyBulletObject : public GameObject {
public:
    EnemyBulletObject(glm::vec3 pos,
        glm::vec3 rot,
        glm::vec3 scale,
        string modelName,
        dWorldID w,
        dSpaceID s);

    virtual void update() override;
    virtual void draw() override;

    float maxSpeed{};
    float maxAccel{};

    float spawnTime = 0;
    float despawnSeconds = 15;

    glm::vec3 targetVelocity{};
};

#endif // ENEMYBULLETOBJECT_H
