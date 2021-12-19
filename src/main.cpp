#include "ofMain.h"
#include "ofApp.h"
#include "ode/ode.h"

ofApp* myApp;

//========================================================================
int main( ){
	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context
    myApp = new ofApp();

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
    ofRunApp(myApp);

}
