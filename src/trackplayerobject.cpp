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

    this->maxSpeed = ofRandom(5, 10);
    this->maxAccel = ofRandom(1, 10);
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

    //targetVelocity = glm::normalize(dirToPlayer + (glm::vec3(ofRandom(-1, 1), ofRandom(-1, 1), 0))) * maxSpeed;
    targetVelocity = glm::normalize(dirToPlayer * maxSpeed);
    //targetVelocity = dirToPlayer * maxSpeed;

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

    ofPushMatrix();

    ofFill();
    ofSetColor(0, 0, 0, 200);
    //ofTranslate(pos.x, pos.y + (this->maxHealth / 10), pos.z + 2.5);
    ofTranslate(pos.x, pos.y, pos.z + 2.5);

    ofRotate(90, 0, 1, 0);
    ofRotate(Utils::dirToAngle(glm::normalize(glm::vec2(targetVelocity))) + 90, 1, 0, 0);

    ofDrawRectangle(0, 0 - (this->maxHealth / 40), 0, 1, this->curHealth / 20);

    ofNoFill();

    ofDrawRectangle(0, 0 - (this->maxHealth / 40), 0, 1, this->maxHealth / 20);

    /*this->curHealth -= 1;
    if (this->curHealth <= 0)
        this->curHealth = this->maxHealth;*/

    ofFill();

    ofPopMatrix();
}
