#include "physicsobject.h"

PhysicsObject::PhysicsObject(glm::vec3 pos,
    glm::vec3 rot,
    glm::vec3 scale,
    string modelName,
    dWorldID w,
    dSpaceID s)
{
    this->init(pos, rot, scale, modelName, true, w, s);
    this->type = PHYSICS_OBJECT;
}

void PhysicsObject::update()
{
}

void PhysicsObject::draw()
{
    GameObject::draw();
}
