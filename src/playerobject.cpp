#include "playerobject.h"

PlayerObject::PlayerObject(glm::vec3 pos, string modelName, dWorldID w, dSpaceID s) : GameObject(pos, modelName, w, s)
{
}

void PlayerObject::update()
{
    const dReal* currentVelocity = dBodyGetLinearVel(m_body);
    glm::vec3 newVelocity = glm::vec3(currentVelocity[0], currentVelocity[1], currentVelocity[2]);

    targetVelocity = glm::vec3(myApp->inputHorizontal, myApp->inputVertical, 0) * maxSpeed;
    float maxAccelThisFrame = maxAccel * ofGetLastFrameTime();

    if (currentVelocity[0] < targetVelocity.x) {
        newVelocity.x = min((float)(currentVelocity[0] + maxAccelThisFrame), targetVelocity.x);
    }
    else if (currentVelocity[0] > targetVelocity.x) {
        newVelocity.x = max((float)(currentVelocity[0] - maxAccelThisFrame), targetVelocity.x);
    }

    if (currentVelocity[1] < targetVelocity.y) {
        newVelocity.y = min((float)(currentVelocity[1] + maxAccelThisFrame), targetVelocity.y);
    }
    else if (currentVelocity[1] > targetVelocity.y) {
        newVelocity.y = max((float)(currentVelocity[1] - maxAccelThisFrame), targetVelocity.y);
    }

    //this->accel = glm::vec3(myApp->inputHorizontal, myApp->inputVertical, 0) * ofGetLastFrameTime();
    //ofLog() << this->accel;
    dBodySetLinearVel(m_body, newVelocity.x, newVelocity.y, newVelocity.z);
    //GameObject::update();
}
