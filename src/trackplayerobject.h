#include "gameobject.h"

#ifndef TRACKPLAYEROBJECT_H
#define TRACKPLAYEROBJECT_H

class TrackPlayerObject : public GameObject {
public:
    TrackPlayerObject(glm::vec3 pos,
        glm::vec3 rot,
        glm::vec3 scale,
        string modelName,
        dWorldID w,
        dSpaceID s);

    virtual void update() override;
    virtual void draw() override;

    float maxSpeed{};
    float maxAccel{};

    float maxHealth = 100;
    float curHealth = maxHealth;

    glm::vec3 targetVelocity{};
};

#endif // TRACKPLAYEROBJECT_H
