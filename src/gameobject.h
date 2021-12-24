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
    /* ODE objects */
    dBodyID m_body;
    dMass   m_mass;
    dGeomID m_geom;

    /* The 3D model */
    ofxAssimpModelLoader m_model;

    /* Attributes of this object */
    ofQuaternion m_rotation;

    virtual void update() = 0;
    virtual void draw() = 0;

    std::vector<std::vector<glm::vec3>> vertices;
    std::vector<std::vector<uint>> indices;

    bool debug_draw = true;
};
#endif // GAMEOBJECT_H
