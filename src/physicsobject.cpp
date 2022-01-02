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
    if (myApp->resetFlag) {
        auto obj = myApp->geomObjectMap.at(m_geom.at(0));
        if (find(myApp->objectsDestroyQueue.begin(), myApp->objectsDestroyQueue.end(), obj) == myApp->objectsDestroyQueue.end()) {
            myApp->objectsDestroyQueue.push_back(obj);
        }
    }
}

void PhysicsObject::draw()
{
    GameObject::draw();
}
