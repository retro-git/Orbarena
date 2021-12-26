#include "playerobject.h"

PlayerObject::PlayerObject(glm::vec3 pos,
    glm::vec3 rot,
    glm::vec3 scale,
    string modelName,
    dWorldID w,
    dSpaceID s)
{
    this->init(pos, rot, scale, modelName, w, s);
    this->type = PLAYER_OBJECT;

    /* Set up physics objects */
    m_body = dBodyCreate(w);
    dBodySetPosition(m_body, pos.x, pos.y, pos.z);
    dGeomSetBody(m_geom, m_body);
}

void PlayerObject::update()
{
    const dReal* currentVelocity = dBodyGetLinearVel(m_body);

    glm::vec3 forward = myApp->cam.getLookAtDir();
    forward.z = 0;
    glm::normalize(forward);
    glm::vec3 right = myApp->cam.getSideDir();
    right.z = 0;
    glm::normalize(right);
    targetVelocity = (forward * myApp->inputVertical + right * myApp->inputHorizontal) * maxSpeed;

    auto moveTowards = [](float start, float end, float maxAccel) {
        if (abs(end - start) <= maxAccel)
            return end;
        else
            return start + glm::sign(end - start) * maxAccel;
        /*if (start < end) {
        return min(start + maxAccel, end);
    }
    else if (start > end) {
        return max(start - maxAccel, end);
    }
    else return start;*/
    };

    dBodySetLinearVel(
        m_body,
        moveTowards(
            currentVelocity[0], targetVelocity.x, maxAccel * ofGetLastFrameTime()),
        moveTowards(
            currentVelocity[1], targetVelocity.y, maxAccel * ofGetLastFrameTime()),
        currentVelocity[2]);
    // GameObject::update();
}

/* Draw method collects latest data from ODE and draws the model at
 * that location/orientation.
 */

void PlayerObject::draw()
{
    GameObject::draw();
}
