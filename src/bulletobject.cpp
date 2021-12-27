#include "bulletobject.h"
#include "utils.h"

BulletObject::BulletObject(glm::vec3 pos,
    glm::vec3 rot,
    glm::vec3 scale,
    string modelName,
    dWorldID w,
    dSpaceID s)
{
    pos.z += 3;
    this->init(pos, rot, scale, modelName, true, w, s);

    const dReal* playerVelocity = dBodyGetLinearVel(myApp->player->m_body);

    glm::vec3 forward = myApp->cam.getLookAtDir();
    forward.z = 0;
    glm::normalize(forward);
    glm::vec3 right = myApp->cam.getSideDir();
    right.z = 0;
    glm::normalize(right);
    targetVelocity = (forward * 1) * maxSpeed;

    dBodySetLinearVel(
        m_body, targetVelocity.x, targetVelocity.y, targetVelocity.z);

    this->type = BULLET_OBJECT;
}

void BulletObject::update()
{
    /*const dReal* currentVelocity = dBodyGetLinearVel(m_body);

    const dReal* playerVelocity = dBodyGetLinearVel(myApp->player->m_body);

    glm::vec3 forward = myApp->cam.getLookAtDir();
    forward.z = 0;
    glm::normalize(forward);
    glm::vec3 right = myApp->cam.getSideDir();
    right.z = 0;
    glm::normalize(right);
    targetVelocity = (forward * 2) * maxSpeed;

    dBodySetLinearVel(
        m_body,
        Utils::moveTowards(
            currentVelocity[0], targetVelocity.x, maxAccel * ofGetLastFrameTime()),
        Utils::moveTowards(
            currentVelocity[1], targetVelocity.y, maxAccel * ofGetLastFrameTime()),
        Utils::currentVelocity[2]);
    // GameObject::update();*/
}

void BulletObject::draw()
{
    GameObject::draw();
}
