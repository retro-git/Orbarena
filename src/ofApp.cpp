#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofDisableArbTex();

    // create world
    dInitODE2(0);
    world = dWorldCreate();
    space = dHashSpaceCreate(0);
    contactgroup = dJointGroupCreate(0);
    dWorldSetGravity(world, 0, 0, -0.5);

    dAllocateODEDataForThread(dAllocateMaskAll);

    /* The light */
    m_light1.setPosition(0, 0, 15);
    m_light1.lookAt(glm::vec3(0, 0, 0));
    m_light1.enable();

    HUDFont.load("verdana.ttf", 18, true, true);

    this->player = std::dynamic_pointer_cast<PlayerObject>(
        createObject<PlayerObject>(glm::vec3(0, 0, 25),
            glm::vec3(0, 0, 0),
            glm::vec3(1, 1, 1),
            "Orbos.dae",
            world,
            space));

    createObject<StaticObject>(glm::vec3(0, 0, 0),
        glm::vec3(90, 0, 0),
        glm::vec3(20, 20, 20),
        "arena/Orb Arena.obj",
        world,
        space);

    cam = FollowCamera(player);
    cam.setNearClip(0.01);
}

void ofApp::startNextWave()
{
    waveCounter++;

    numEnemies = ceil(ofRandom(ceil(waveCounter / 2), waveCounter));
    ofLog() << ceil(waveCounter / 2);
    ofLog() << numEnemies;
    for (int i = 0; i < numEnemies; i++) {
        objectsCreateQueue.push_back({ TRACK_PLAYER_OBJECT, glm::vec3(ofRandom(0, 25), ofRandom(0, 25), 15), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), "Orbos.dae", world, space });
    }
}

void ofApp::createQueuedObjects()
{
    for (auto& obj : objectsCreateQueue) {
        switch (obj.type) {
        case ENEMY_BULLET_OBJECT:
            createObject<EnemyBulletObject>(obj.pos, obj.rot, obj.scale, obj.modelName, obj.w, obj.s);
            break;
        case BULLET_OBJECT:
            createObject<BulletObject>(obj.pos, obj.rot, obj.scale, obj.modelName, obj.w, obj.s);
            break;
        case TRACK_PLAYER_OBJECT:
            createObject<TrackPlayerObject>(obj.pos, obj.rot, obj.scale, obj.modelName, obj.w, obj.s);
            break;
        case STATIC_OBJECT:
            createObject<StaticObject>(obj.pos, obj.rot, obj.scale, obj.modelName, obj.w, obj.s);
            break;
        case PLAYER_OBJECT:
            createObject<PlayerObject>(obj.pos, obj.rot, obj.scale, obj.modelName, obj.w, obj.s);
            break;
        }
    }
    objectsCreateQueue.clear();
}

template <typename T>
std::shared_ptr<GameObject>
ofApp::createObject(glm::vec3 pos,
    glm::vec3 rot,
    glm::vec3 scale,
    string modelName,
    dWorldID w,
    dSpaceID s)
{
    std::shared_ptr<GameObject> obj = std::make_shared<T>(pos, rot, scale, modelName, w, s);
    objects.push_back(obj);

    for (auto& geom : objects.back()->m_geom) {
        geomObjectMap.insert({ geom, objects.back() });
    }

    return obj;
}

void ofApp::destroyQueuedObjects()
{
    for (auto& obj : objectsDestroyQueue) {
        destroyObject(obj);
    }
    objectsDestroyQueue.clear();
}

void ofApp::destroyObject(std::shared_ptr<GameObject> obj)
{
    int i = 0;
    for (auto& geom : obj->m_geom) {
        ofLog() << "destroying geom of type " << obj->type;
        ofLog() << obj;
        ofLog() << i;
        i++;
        dGeomDestroy(geom);
        geomObjectMap.erase(geom);
    }

    for (auto& data : obj->m_data) {
        dGeomTriMeshDataDestroy(data);
    }

    if (obj->type != STATIC_OBJECT) {
        dBodyDestroy(obj->m_body);
    }

    auto it = find(objects.begin(), objects.end(), obj);
    objects.erase(it);
}

//--------------------------------------------------------------
void ofApp::update()
{
    if (numEnemies == 0)
        startNextWave();

    for (auto x : objects)
        x->update();

    cam.update();

    this->inputMouseHorizontal = 0;
    this->inputMouseVertical = 0;

    dSpaceCollide(space, 0, &nearCallback);
    dWorldStep(world, 0.05);

    // remove all contact joints
    dJointGroupEmpty(contactgroup);

    destroyQueuedObjects();
    createQueuedObjects();
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofFill();
    ofBackground(20);
    cam.begin();

    ofEnableDepthTest();

    for (auto x : objects)
        x->draw();

    cam.end();

    ofDisableDepthTest();

    ofSetColor(255, 255, 200, 255);
    string wave = "WAVE: " + std::to_string(waveCounter);
    HUDFont.drawString(wave, 10, 30);

    ofSetColor(0, 128, 0, 200);
    string health = "HEALTH:";
    ofRectangle bounds = HUDFont.getStringBoundingBox(health, 0, 0);
    HUDFont.drawString(health, (ofGetWidth() / 2) - (bounds.width / 2), ofGetHeight() - 110);

    ofDrawRectangle(ofGetWidth() / 2 - ((this->player->maxHealth) / 2), ofGetHeight() - 100, this->player->curHealth, 50);

    ofNoFill();

    ofDrawRectangle(ofGetWidth() / 2 - ((this->player->maxHealth) / 2), ofGetHeight() - 100, this->player->maxHealth, 50);

    // ofDrawBitmapString("Hello World", ofGetWindowWidth() /2,
    // ofGetWindowHeight() /2);
}

void ofApp::collide(dGeomID o1, dGeomID o2)
{
    auto obj1 = geomObjectMap.at(o1);
    auto obj2 = geomObjectMap.at(o2);

    const int N = 10;
    dContact contact[N];
    int n = dCollide(o1, o2, N, &contact[0].geom, sizeof(dContact));
    if (n > 0) {
        for (int i = 0; i < n; i++) {
            if (((obj1->type == BULLET_OBJECT || obj2->type == BULLET_OBJECT) || (obj1->type == ENEMY_BULLET_OBJECT || obj2->type == ENEMY_BULLET_OBJECT)) && (obj1->type == STATIC_OBJECT || obj2->type == STATIC_OBJECT)) {
                if (contact[i].geom.normal[2] < 0.7f) {
                    if (obj1->type == BULLET_OBJECT || obj1->type == ENEMY_BULLET_OBJECT)
                        if (find(objectsDestroyQueue.begin(), objectsDestroyQueue.end(), obj1) == objectsDestroyQueue.end())
                            objectsDestroyQueue.push_back(obj1);
                    if (obj2->type == BULLET_OBJECT || obj2->type == ENEMY_BULLET_OBJECT)
                        if (find(objectsDestroyQueue.begin(), objectsDestroyQueue.end(), obj2) == objectsDestroyQueue.end())
                            objectsDestroyQueue.push_back(obj2);
                    return;
                }
            }
            if ((obj1->type == BULLET_OBJECT || obj2->type == BULLET_OBJECT) && (obj1->type == TRACK_PLAYER_OBJECT || obj2->type == TRACK_PLAYER_OBJECT)) {
                if (obj1->type == TRACK_PLAYER_OBJECT) {
                    std::dynamic_pointer_cast<TrackPlayerObject>(obj1)->targetHealth -= 10;
                }
                if (obj2->type == TRACK_PLAYER_OBJECT) {
                    std::dynamic_pointer_cast<TrackPlayerObject>(obj2)->targetHealth -= 10;
                }
                if (obj1->type == BULLET_OBJECT)
                    if (find(objectsDestroyQueue.begin(), objectsDestroyQueue.end(), obj1) == objectsDestroyQueue.end())
                        objectsDestroyQueue.push_back(obj1);
                if (obj2->type == BULLET_OBJECT)
                    if (find(objectsDestroyQueue.begin(), objectsDestroyQueue.end(), obj2) == objectsDestroyQueue.end())
                        objectsDestroyQueue.push_back(obj2);
                return;
            }
            if ((obj1->type == ENEMY_BULLET_OBJECT || obj2->type == ENEMY_BULLET_OBJECT) && (obj1->type == PLAYER_OBJECT || obj2->type == PLAYER_OBJECT)) {
                if (obj1->type == PLAYER_OBJECT) {
                    std::dynamic_pointer_cast<PlayerObject>(obj1)->targetHealth -= 10;
                }
                if (obj2->type == PLAYER_OBJECT) {
                    std::dynamic_pointer_cast<PlayerObject>(obj2)->targetHealth -= 10;
                }
                if (obj1->type == ENEMY_BULLET_OBJECT)
                    if (find(objectsDestroyQueue.begin(), objectsDestroyQueue.end(), obj1) == objectsDestroyQueue.end())
                        objectsDestroyQueue.push_back(obj1);
                if (obj2->type == ENEMY_BULLET_OBJECT)
                    if (find(objectsDestroyQueue.begin(), objectsDestroyQueue.end(), obj2) == objectsDestroyQueue.end())
                        objectsDestroyQueue.push_back(obj2);
                return;
            }
            // contact[i].geom.normal
            contact[i].surface.mode = dContactSlip1 | dContactSlip2 | dContactSoftERP | dContactSoftCFM | dContactApprox1;
            contact[i].surface.mu = 0.08;
            contact[i].surface.slip1 = 0.1;
            contact[i].surface.slip2 = 0.1;
            contact[i].surface.soft_erp = 0.5;
            contact[i].surface.soft_cfm = 0.3;
            dJointID c = dJointCreateContact(world, contactgroup, &contact[i]);
            dJointAttach(
                c, dGeomGetBody(contact[i].geom.g1), dGeomGetBody(contact[i].geom.g2));
        }
    }
}

static void
nearCallback(void*, dGeomID o1, dGeomID o2)
{
    myApp->collide(o1, o2);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    switch (key) {
    case 'w':
    case 'W':
        this->inputVertical = 1;
        break;
    case 'a':
    case 'A':
        this->inputHorizontal = -1;
        break;
    case 's':
    case 'S':
        this->inputVertical = -1;
        break;
    case 'd':
    case 'D':
        this->inputHorizontal = 1;
        break;
    case 'q':
        ofExit();
        break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
    switch (key) {
    case 'w':
    case 'W':
        this->inputVertical = 0;
        break;
    case 'a':
    case 'A':
        this->inputHorizontal = 0;
        break;
    case 's':
    case 'S':
        this->inputVertical = 0;
        break;
    case 'd':
    case 'D':
        this->inputHorizontal = 0;
        break;
    case 'f':
    case 'F':
        this->cam.lookAngles.x += 1;
        break;
    case 'g':
    case 'G':
        this->cam.lookAngles.y += 1;
        break;
    case 'q':
        ofExit();
        break;
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
    auto curMousePosition = glm::vec2(x, y);
    glm::vec2 delta = glm::vec2(x, y) - prevMousePosition;
    if (glm::length(delta) > 60.f) {
        prevMousePosition = curMousePosition;
        return;
    }
    this->inputMouseHorizontal = delta.x;
    this->inputMouseVertical = delta.y;
    prevMousePosition = curMousePosition;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    createObject<BulletObject>(player->pos,
        glm::vec3(0, 0, 90),
        glm::vec3(0.5, 0.5, 0.5),
        "Orbos.dae",
        world,
        space);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}
