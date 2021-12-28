#include "playerobject.h"
#include "utils.h"

PlayerObject::PlayerObject(glm::vec3 pos,
    glm::vec3 rot,
    glm::vec3 scale,
    string modelName,
    dWorldID w,
    dSpaceID s)
{
    this->init(pos, rot, scale, modelName, true, w, s);
    this->type = PLAYER_OBJECT;
}

void PlayerObject::update()
{
    const dReal* currentVelocity = dBodyGetLinearVel(m_body);

    if (myApp->inputVertical == 0 && myApp->inputHorizontal == 0)
        return;

    glm::vec3 forward = myApp->cam.getLookAtDir();
    forward.z = 0;
    glm::normalize(forward);
    glm::vec3 right = myApp->cam.getSideDir();
    right.z = 0;
    glm::normalize(right);
    targetVelocity = (forward * myApp->inputVertical + right * myApp->inputHorizontal) * maxSpeed;

    dBodySetLinearVel(
        m_body,
        Utils::moveTowards(
            currentVelocity[0], targetVelocity.x, maxAccel * ofGetLastFrameTime()),
        Utils::moveTowards(
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
