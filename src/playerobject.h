#include "gameobject.h"

#ifndef PLAYEROBJECT_H
#define PLAYEROBJECT_H

class PlayerObject : public GameObject
{
public:
    PlayerObject(glm::vec3 pos, string modelName, dWorldID w, dSpaceID s);

    virtual void update() override;

    float maxSpeed = 10;
    float maxAccel = 10;

    glm::vec3 targetVelocity{};
};

#endif // PLAYEROBJECT_H
