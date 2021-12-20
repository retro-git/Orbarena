#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofDisableArbTex();

    dMass m;

    // create world
    dInitODE2(0);
    world = dWorldCreate();
    space = dHashSpaceCreate (0);
    contactgroup = dJointGroupCreate (0);
    dWorldSetGravity (world,0,0,-0.5);
    ground = dCreatePlane (space,0,0,1,0);

    ofVec3f upVector;
    upVector.set(0, 0, 1);
    //cam.setAutoDistance(false);
    cam.setNearClip(0.01);
    //cam.setPosition(10,10,10);
    cam.setOrientation(glm::vec3(40, 0, 0));
    //cam.lookAt({0,0,0},upVector);
    //cam.setUpAxis(upVector);

    dAllocateODEDataForThread(dAllocateMaskAll);

    /* The light */
    m_light1.setPosition(8,8,5);
    m_light1.lookAt(glm::vec3(0,0,0));
    m_light1.enable();

    for(unsigned int p=0; p<1; p++) {
        //objects.push_back(new GameObject(ofRandom(-5,5), ofRandom(-5,5), ofRandom(0,10), "Dragon 2.5_dae.dae", world, space) );
        //objects.push_back(new GameObject(0, 0, 200*(p+1), "Test.dae", world, space) );
        objects.push_back(new PlayerObject(glm::vec3(0, 0, 200*(p+1)), "Test.dae", world, space) );
    }

    skybox.load();
}

//--------------------------------------------------------------
void ofApp::update(){
    for(auto x: objects) x->update();

    const dReal *buggyPos = dBodyGetPosition(this->objects[0]->m_body);
    glm::vec3 focusPoint = glm::vec3(buggyPos[0], buggyPos[1], buggyPos[2]);
    glm::vec3 lookDir = cam.getLookAtDir();
    cam.setPosition(focusPoint - lookDir * 10);

    dSpaceCollide (space,0,&nearCallback);

    dWorldStep (world,0.05);

    // remove all contact joints
    dJointGroupEmpty (contactgroup);
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(20);
    cam.begin();

    skybox.draw();

    ofEnableDepthTest();

    for(auto x: objects) x->draw();

    ofDisableDepthTest();
    cam.end();
}

void ofApp::collide(dGeomID o1, dGeomID o2)
{
  int i,n;

  // only collide things with the ground
  int g1 = (o1 == ground);
  int g2 = (o2 == ground);
  //if (!(g1 ^ g2)) return;

  //if (this->objects[0]->m_geom == o1 && this->objects[1]->m_geom == o2 || this->objects[0]->m_geom == o2 && this->objects[1]->m_geom == o1 ) {
  //    ofLog(OF_LOG_NOTICE, "DRAGONS");
  //}

  const int N = 10;
  dContact contact[N];
  n = dCollide (o1,o2,N,&contact[0].geom,sizeof(dContact));
  if (n > 0) {
    for (i=0; i<n; i++) {
      contact[i].surface.mode = dContactSlip1 | dContactSlip2 |
        dContactSoftERP | dContactSoftCFM | dContactApprox1;
      contact[i].surface.mu = 0.08;
      contact[i].surface.slip1 = 0.1;
      contact[i].surface.slip2 = 0.1;
      contact[i].surface.soft_erp = 0.5;
      contact[i].surface.soft_cfm = 0.3;
      dJointID c = dJointCreateContact (world,contactgroup,&contact[i]);
      dJointAttach (c,
                    dGeomGetBody(contact[i].geom.g1),
                    dGeomGetBody(contact[i].geom.g2));
    }
  }
}

static void nearCallback (void *, dGeomID o1, dGeomID o2) {
    myApp->collide(o1,o2);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key) {
    case 'w': case 'W':
      this->inputVertical = 1;
      break;
    case 'a': case 'A':
        this->inputHorizontal = -1;
      break;
    case 's': case 'S':
        this->inputVertical = -1;
      break;
    case 'd': case 'D':
        this->inputHorizontal = 1;
      break;
    case 'q':
        ofExit();
        break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    switch(key) {
    case 'w': case 'W':
      this->inputVertical = 0;
      break;
    case 'a': case 'A':
        this->inputHorizontal = 0;
      break;
    case 's': case 'S':
        this->inputVertical = 0;
      break;
    case 'd': case 'D':
        this->inputHorizontal = 0;
      break;
    case 'q':
        ofExit();
        break;
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
