#include "gameobject.h"

#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

class PhysicsObject : public GameObject {
public:
    PhysicsObject(glm::vec3 pos,
        glm::vec3 rot,
        glm::vec3 scale,
        string modelName,
        dWorldID w,
        dSpaceID s);

    virtual void update() override;
    virtual void draw() override;
};

#endif // PHYSICSOBJECT_H
