#include "ofCamera.h"
#include "ode/ode.h"
#include "ofApp.h"
#include "playerobject.h"

#ifndef FOLLOWCAMERA_H
#define FOLLOWCAMERA_H


class FollowCamera : public ofCamera
{
public:
    FollowCamera();
    FollowCamera(PlayerObject* followObject);

    void update();
    void updateFollowPoint();
    bool autoAlign();

    PlayerObject* followObject;
    glm::vec3 followPoint{};
    glm::vec3 prevFollowPoint{};
    glm::vec2 lookAngles = glm::vec2(45, 0);
    float followPointRadius = 10;
    float rotationMaxAccel = 90;
    float alignmentAngleRange = 80;
};

#endif // FOLLOWCAMERA_H
