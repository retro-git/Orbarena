#include "gameobject.h"

#ifndef PLAYEROBJECT_H
#define PLAYEROBJECT_H

class PlayerObject : public GameObject {
public:
    PlayerObject(glm::vec3 pos,
        glm::vec3 rot,
        glm::vec3 scale,
        string modelName,
        dWorldID w,
        dSpaceID s);

    virtual void update() override;
    virtual void draw() override;

    float maxSpeed = 8;
    float maxAccel = 8;

    float maxHealth = 100;
    float curHealth = maxHealth;
    float targetHealth = curHealth;

    float maxHealthLossSpeed{ 50 };

    glm::vec3 targetVelocity{};
};

#endif // PLAYEROBJECT_H
