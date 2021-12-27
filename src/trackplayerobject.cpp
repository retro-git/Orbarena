#include "trackplayerobject.h"
#include "utils.h"

TrackPlayerObject::TrackPlayerObject(glm::vec3 pos,
    glm::vec3 rot,
    glm::vec3 scale,
    string modelName,
    dWorldID w,
    dSpaceID s)
{
    this->init(pos, rot, scale, modelName, true, w, s);
    this->type = TRACK_PLAYER_OBJECT;
}

void TrackPlayerObject::update()
{
    const dReal* currentVelocity = dBodyGetLinearVel(m_body);

    //if (myApp->inputVertical == 0 && myApp->inputHorizontal == 0)
    // return;

    const dReal* currentPosition = dBodyGetPosition(m_body);
    const dReal* playerPosition = dBodyGetPosition(myApp->player->m_body);
    glm::vec3 dirToPlayer = glm::normalize(
        glm::vec3(playerPosition[0], playerPosition[1], playerPosition[2]) - glm::vec3(currentPosition[0], currentPosition[1], currentPosition[2]));

    targetVelocity = dirToPlayer * maxSpeed;

    dBodySetLinearVel(
        m_body,
        Utils::moveTowards(
            currentVelocity[0], targetVelocity.x, maxAccel * ofGetLastFrameTime()),
        Utils::moveTowards(
            currentVelocity[1], targetVelocity.y, maxAccel * ofGetLastFrameTime()),
        currentVelocity[2]);
    // GameObject::update();
}

void TrackPlayerObject::draw()
{
    GameObject::draw();
}
