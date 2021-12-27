#include "staticobject.h"
#include "ode/ode.h"

StaticObject::StaticObject(glm::vec3 pos,
    glm::vec3 rot,
    glm::vec3 scale,
    string modelName,
    dWorldID w,
    dSpaceID s)
{
    this->init(pos, rot, scale, modelName, false, w, s);
    this->type = STATIC_OBJECT;
}

void StaticObject::update()
{
}

void StaticObject::draw()
{
    /* Draw the model: */
    m_model.drawFaces();
}
