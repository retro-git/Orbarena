#include "ode/ode.h"
#include "ofApp.h"
#include "ofCamera.h"
#include "playerobject.h"

#ifndef FOLLOWCAMERA_H
#define FOLLOWCAMERA_H

class FollowCamera : public ofCamera {
public:
    FollowCamera();
    FollowCamera(std::shared_ptr<PlayerObject> followObject);

    void update();
    void updateFollowPoint();
    bool playerControl();
    void autoControl();

    std::shared_ptr<PlayerObject> followObject;
    glm::vec3 followPoint{};
    glm::vec3 prevFollowPoint{};
    glm::vec2 lookAngles = glm::vec2(45, 0);

    float followPointRadius = 10;
    float rotationMaxAccel = 90;
    float alignmentAngleRange = 80;
    float camDistance = 20;
    float autoControlDelay = 1;
    float sensitivity = 1.3;

    float lastPlayerControlTimestamp{};
};

#endif // FOLLOWCAMERA_H
