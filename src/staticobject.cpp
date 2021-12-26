#include "staticobject.h"
#include "ode/ode.h"

StaticObject::StaticObject(glm::vec3 pos,
    glm::vec3 rot,
    glm::vec3 scale,
    string modelName,
    dWorldID w,
    dSpaceID s)
{
    this->init(pos, rot, scale, modelName, w, s);
    this->type = STATIC_OBJECT;
}

void StaticObject::init(glm::vec3 pos,
    glm::vec3 rot,
    glm::vec3 scale,
    string modelName,
    dWorldID w,
    dSpaceID s)
{
    GameObject::init(pos, rot, scale, modelName, w, s);
}

void StaticObject::update()
{
}

void StaticObject::draw()
{
    /* Draw the model: */
    m_model.drawFaces();
}
