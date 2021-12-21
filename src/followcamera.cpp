#include "followcamera.h"

FollowCamera::FollowCamera()
{

}

FollowCamera::FollowCamera(PlayerObject* followObject) : followObject(followObject)
{
}

void FollowCamera::updateFollowPoint()
{
    this->prevFollowPoint = followPoint;

    const dReal *bodyPosODE = dBodyGetPosition(followObject->m_body);
    glm::vec3 bodyPos = glm::vec3(bodyPosODE[0], bodyPosODE[1], bodyPosODE[2]);

    auto lerp = [](glm::vec3 x, glm::vec3 y, float a) {
        return x * (1.0 - a) + y * a;
    };

    if (followPointRadius <= 0.1)
    {
        this->followPoint = bodyPos;
    }
    else
    {
        float lerpAlpha = 1;
        if (auto dist = glm::distance(bodyPos, this->followPoint); dist > 0.1)
        {
            lerpAlpha = min(pow(0.1, ofGetLastFrameTime()), (double)(followPointRadius / dist));
        }
        this->followPoint = lerp(bodyPos, this->followPoint, lerpAlpha);
    }
}

bool FollowCamera::autoAlign()
{
    glm::vec2 diff = glm::vec2(followPoint - prevFollowPoint);

    if (glm::length2(diff) < 0.001) {
        return false;
    }

    float rotationMaxAccelThisFrame = rotationMaxAccel * ofGetLastFrameTime();

    auto dirToAngle = [](glm::vec2 dir) {
        if (float angle = glm::degrees(acos(dir.y)); dir.x >= 0) return angle;
        else return 360-angle;
    };

    auto moveTowards = [](float start, float end, float maxAccel) {
        if (abs(end - start) <= maxAccel) return end;
        else return start + glm::sign(end - start) * maxAccel;
    };

    auto angleDelta = [](float start, float end) {
        float d = fmod(end - start, 360);
        if (d > 180.f) d -= 360.f;
        return d;
    };

    auto moveTowardsAngle = [&moveTowards, &angleDelta](float start, float end, float maxAccel) {
        float delta = angleDelta(start, end);

        if (-maxAccel < delta && delta < maxAccel) return end;
        return moveTowards(start, start + delta, maxAccel);
    };

    float targetRotDiffAbs = abs(angleDelta(lookAngles.y, dirToAngle(glm::normalize(diff))));
    if(targetRotDiffAbs < alignmentAngleRange)
    {
        rotationMaxAccelThisFrame *= targetRotDiffAbs / alignmentAngleRange;
    }
    else if (180.f - targetRotDiffAbs < alignmentAngleRange) {
        rotationMaxAccelThisFrame *= (180.f - targetRotDiffAbs) / alignmentAngleRange;
    }

    lookAngles.y = moveTowardsAngle(lookAngles.y, dirToAngle(glm::normalize(diff)), rotationMaxAccelThisFrame);

    //lookAngles.y = dirToAngle(glm::normalize(diff));

    return true;
}

void FollowCamera::update()
{
    updateFollowPoint();
    autoAlign();

    glm::quat rotation = glm::quat(glm::vec3(glm::radians(lookAngles.x), 0, glm::radians(-lookAngles.y)));
    glm::vec3 lookDir = glm::rotate(rotation, glm::vec3(0, 0, -1));
    glm::vec3 pos = followPoint - lookDir * 20;

    this->setPosition(pos);
    this->setOrientation(rotation);

}
