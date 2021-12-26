#include "followcamera.h"

FollowCamera::FollowCamera() {}

FollowCamera::FollowCamera(std::shared_ptr<PlayerObject> followObject)
    : followObject(followObject)
{
}

void FollowCamera::updateFollowPoint()
{
    this->prevFollowPoint = followPoint;

    const dReal* bodyPosODE = dBodyGetPosition(followObject->m_body);
    glm::vec3 bodyPos = glm::vec3(bodyPosODE[0], bodyPosODE[1], bodyPosODE[2]);

    auto lerp = [](glm::vec3 x, glm::vec3 y, float a) {
        return x * (1.0 - a) + y * a;
    };

    if (followPointRadius <= 0.1) {
        this->followPoint = bodyPos;
    } else {
        float lerpAlpha = 1;
        auto dist = glm::distance(bodyPos, this->followPoint);
        if (dist > 0.1) {
            lerpAlpha = min(pow(0.1, ofGetLastFrameTime()), (double)(followPointRadius / dist));
        }
        this->followPoint = lerp(bodyPos, this->followPoint, lerpAlpha);
    }
}

bool FollowCamera::playerControl()
{
    if (myApp->inputMouseVertical != 0 || myApp->inputMouseHorizontal != 0) {
        this->lookAngles += rotationMaxAccel * ofGetLastFrameTime() * (glm::vec2(-myApp->inputMouseVertical, myApp->inputMouseHorizontal) * sensitivity);
        if (lookAngles.y < 0)
            lookAngles.y += 360;
        else if (lookAngles.y >= 360)
            lookAngles.y -= 360;

        this->lookAngles.x = glm::clamp(lookAngles.x, 15.f, 90.f);
        this->lastPlayerControlTimestamp = ofGetElapsedTimef();
        // ofLog() << lookAngles.x;
        // ofLog() << lookAngles.x;
        return true;
    }

    return false;
}

void FollowCamera::autoControl()
{
    glm::vec2 diff = glm::vec2(followPoint - prevFollowPoint);

    if (glm::length2(diff) < 0.001) {
        return;
    }

    float rotationMaxAccelThisFrame = rotationMaxAccel * ofGetLastFrameTime();

    auto dirToAngle = [](glm::vec2 dir) {
        float angle = glm::degrees(acos(dir.y));
        if (dir.x >= 0)
            return angle;
        else
            return 360 - angle;
    };

    auto moveTowards = [](float start, float end, float maxAccel) {
        if (abs(end - start) <= maxAccel)
            return end;
        else
            return start + glm::sign(end - start) * maxAccel;
    };

    auto angleDelta = [](float start, float end) {
        float d = fmod(end - start, 360);
        if (d > 180.f)
            d -= 360.f;
        return d;
    };

    auto moveTowardsAngle =
        [&moveTowards, &angleDelta](float start, float end, float maxAccel) {
            float delta = angleDelta(start, end);

            if (-maxAccel < delta && delta < maxAccel)
                return end;
            return moveTowards(start, start + delta, maxAccel);
        };

    // scale down rotation accel for smaller adjustments
    float targetRotDiffAbs = abs(angleDelta(lookAngles.y, dirToAngle(glm::normalize(diff))));
    if (targetRotDiffAbs < alignmentAngleRange) {
        rotationMaxAccelThisFrame *= targetRotDiffAbs / alignmentAngleRange;
    } else if (180.f - targetRotDiffAbs < alignmentAngleRange) {
        rotationMaxAccelThisFrame *= (180.f - targetRotDiffAbs) / alignmentAngleRange;
    }

    lookAngles.y = moveTowardsAngle(
        lookAngles.y, dirToAngle(glm::normalize(diff)), rotationMaxAccelThisFrame);

    // lookAngles.y = dirToAngle(glm::normalize(diff));
}

void FollowCamera::update()
{
    updateFollowPoint();

    bool bPlayerControlled = playerControl();
    if (!(bPlayerControlled)) {
        if (ofGetElapsedTimef() - lastPlayerControlTimestamp > autoControlDelay)
            autoControl();
    }

    glm::quat rotation = glm::quat(
        glm::vec3(glm::radians(lookAngles.x), 0, glm::radians(-lookAngles.y)));
    glm::vec3 lookDir = glm::rotate(rotation, glm::vec3(0, 0, -1));
    glm::vec3 pos = followPoint - lookDir * camDistance;

    this->setPosition(pos);
    this->setOrientation(rotation);
}
