#include "playerobject.h"

PlayerObject::PlayerObject(glm::vec3 pos, string modelName, dWorldID w, dSpaceID s) : GameObject(pos, modelName, w, s)
{
}

void PlayerObject::update()
{
    this->accel = glm::vec3(myApp->inputHorizontal, myApp->inputVertical, 0) * ofGetLastFrameTime();
    ofLog() << this->accel;
    GameObject::update();
}
