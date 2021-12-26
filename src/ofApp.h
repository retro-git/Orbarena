#pragma once

#include "ofMain.h"
#include "ode/ode.h"
#include "gameobject.h"
#include "playerobject.h"
#include "followcamera.h"
#include "staticobject.h"
#include "physicsobject.h"
#include "bulletobject.h"

#include "ofxAssimpModelLoader.h"

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

        FollowCamera cam;

        dWorldID world;
        dSpaceID space;
        dJointGroupID contactgroup;
        //dGeomID ground;

        std::vector<std::shared_ptr<GameObject>> objects;

        /* A light */
        ofLight m_light1;

        glm::vec2 prevMousePosition;

        float inputVertical{};
        float inputHorizontal{};
        float inputMouseVertical{};
        float inputMouseHorizontal{};

        std::shared_ptr<PlayerObject> player;
		
};

static void nearCallback (void *, dGeomID o1, dGeomID o2);
extern ofApp *myApp;
