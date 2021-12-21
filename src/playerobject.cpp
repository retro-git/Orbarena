#include "playerobject.h"

PlayerObject::PlayerObject(glm::vec3 pos, string modelName, dWorldID w, dSpaceID s) : GameObject(pos, modelName, w, s)
{
}

void PlayerObject::update()
{
    const dReal* currentVelocity = dBodyGetLinearVel(m_body);
    glm::vec3 newVelocity = glm::vec3(currentVelocity[0], currentVelocity[1], currentVelocity[2]);

    targetVelocity = glm::vec3(myApp->inputHorizontal, myApp->inputVertical, 0) * maxSpeed;

    auto moveTowards = [](float start, float end, float maxAccel) {
        if (abs(end - start) <= maxAccel) return end;
        else return start + glm::sign(end - start) * maxAccel;
        /*if (start < end) {
            return min(start + maxAccel, end);
        }
        else if (start > end) {
            return max(start - maxAccel, end);
        }
        else return start;*/
    };

    dBodySetLinearVel(m_body,
                      moveTowards(currentVelocity[0], targetVelocity.x, maxAccel * ofGetLastFrameTime()),
                      moveTowards(currentVelocity[1], targetVelocity.y, maxAccel * ofGetLastFrameTime()),
                      newVelocity.z);
    //GameObject::update();
}
