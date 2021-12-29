#include "enemybulletobject.h"
#include "utils.h"

EnemyBulletObject::EnemyBulletObject(glm::vec3 pos,
    glm::vec3 rot,
    glm::vec3 scale,
    string modelName,
    dWorldID w,
    dSpaceID s)
{
    pos.z += 2.5;
    this->init(pos, rot, scale, modelName, true, w, s);
    this->type = ENEMY_BULLET_OBJECT;
    this->spawnTime = ofGetElapsedTimef();

    const dReal* currentPosition = dBodyGetPosition(m_body);
    const dReal* playerPosition = dBodyGetPosition(myApp->player->m_body);
    glm::vec3 dirToPlayer = glm::normalize(
        glm::vec3(playerPosition[0], playerPosition[1], playerPosition[2]) - glm::vec3(currentPosition[0], currentPosition[1], currentPosition[2]));

    targetVelocity = dirToPlayer * maxSpeed;

    dBodySetLinearVel(
        m_body, targetVelocity.x, targetVelocity.y, targetVelocity.z);
}

void EnemyBulletObject::update()
{
    if (myApp->resetFlag || ofGetElapsedTimef() - spawnTime > despawnSeconds) {
        auto obj = myApp->geomObjectMap.at(m_geom.at(0));
        if (find(myApp->objectsDestroyQueue.begin(), myApp->objectsDestroyQueue.end(), obj) == myApp->objectsDestroyQueue.end()) {
            myApp->objectsDestroyQueue.push_back(obj);
        }
    }
    /*const dReal* currentVelocity = dBodyGetLinearVel(m_body);

    //if (myApp->inputVertical == 0 && myApp->inputHorizontal == 0)
    // return;

    const dReal* currentPosition = dBodyGetPosition(m_body);
    const dReal* playerPosition = dBodyGetPosition(myApp->player->m_body);
    glm::vec3 dirToPlayer = glm::normalize(
        glm::vec3(playerPosition[0], playerPosition[1], playerPosition[2]) - glm::vec3(currentPosition[0], currentPosition[1], currentPosition[2]));

    //targetVelocity = glm::normalize(dirToPlayer + (glm::vec3(ofRandom(-1, 1), ofRandom(-1, 1), 0))) * maxSpeed;
    targetVelocity = dirToPlayer * maxSpeed;

    dBodySetLinearVel(
        m_body,
        Utils::moveTowards(
            currentVelocity[0], targetVelocity.x, maxAccel * ofGetLastFrameTime()),
        Utils::moveTowards(
            currentVelocity[1], targetVelocity.y, maxAccel * ofGetLastFrameTime()),
        currentVelocity[2]);*/
}

void EnemyBulletObject::draw()
{
    GameObject::draw();
    //m_model.getMesh(0).setColor();
}
