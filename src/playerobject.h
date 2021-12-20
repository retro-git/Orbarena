#include "gameobject.h"

#ifndef PLAYEROBJECT_H
#define PLAYEROBJECT_H

class PlayerObject : public GameObject
{
public:
    PlayerObject(glm::vec3 pos, string modelName, dWorldID w, dSpaceID s);

    virtual void update() override;
};

#endif // PLAYEROBJECT_H
