#include "physicsobject.h"

PhysicsObject::PhysicsObject(glm::vec3 pos,
    glm::vec3 rot,
    glm::vec3 scale,
    string modelName,
    dWorldID w,
    dSpaceID s)
{
    this->init(pos, rot, scale, modelName, w, s);
    this->type = PHYSICS_OBJECT;

    /* Set up physics objects */
    m_body = dBodyCreate(w);
    dBodySetPosition(m_body, pos.x, pos.y, pos.z);
    dGeomSetBody(m_geom, m_body);
}

void PhysicsObject::update()
{
}

void PhysicsObject::draw()
{
    GameObject::draw();
}
