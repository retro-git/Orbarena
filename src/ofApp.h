#pragma once

#include "ofMain.h"
#include "ode/ode.h"
#include "gameobject.h"
#include "playerobject.h"

#include "ofxAssimpModelLoader.h"
#include "ofxSkyBox.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        void collide (dGeomID o1, dGeomID o2);

        ofCamera cam;
        ofxSkyBox skybox;

        dWorldID world;
        dSpaceID space;
        dJointGroupID contactgroup;
        dGeomID ground;

        std::vector<GameObject*> objects;

        /* A light */
        ofLight m_light1;

        float inputVertical;
        float inputHorizontal;
		
};

static void nearCallback (void *, dGeomID o1, dGeomID o2);
extern ofApp *myApp;
