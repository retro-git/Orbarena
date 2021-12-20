#include "ode/ode.h"
#include "ofApp.h"
#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

/* This class wraps an ODE physics entity and its graphics elements
 * together into a single game object.
 */
class GameObject
{
public:
    GameObject(float x, float y, float z, string modelName, dWorldID w, dSpaceID s);

    /* ODE objects */
    dBodyID m_body;
    dMass   m_mass;
    dGeomID m_geom;

    /* The 3D model */
    ofxAssimpModelLoader m_model;

    /* Attributes of this object */
    float x, y, z;
    glm::vec3 accel{};
    ofQuaternion m_rotation;

    void setPosition(float x, float y, float z);
    void update();
    void draw();

    bool debug_draw = false;

    /* The length, width, height of the object */
    const float c_len=1,c_wid=1,c_hei=0.1;
};
#endif // GAMEOBJECT_H
