#include "gameobject.h"
#include "ode/ode.h"

template<typename T> struct TD;

GameObject::GameObject(glm::vec3 pos, glm::vec3 rot, string modelName, dWorldID w, dSpaceID s)
{
    /* Set our x,y,z variables */
    this->pos = pos;

    /* Set up graphics objects */
    m_model.loadModel(modelName);
    this->vertices = m_model.getMesh(0).getVertices();
    this->indices = m_model.getMesh(0).getIndices();

    m_model.setRotation(0,rot.x,1,0,0);
    m_model.setRotation(1,rot.y,0,1,0);
    m_model.setRotation(2,rot.z,0,0,1);
    double scale = 1.0/ m_model.getNormalizedScale();
    m_model.setScale(scale,scale,scale);

    /* Set up physics objects */
    m_body = dBodyCreate(w);
    dBodySetPosition(m_body, pos.x, pos.y, pos.z);
    ofMesh m = m_model.getMesh(0);
    dTriMeshDataID data = dGeomTriMeshDataCreate();
    dGeomTriMeshDataBuildSingle(data, &this->vertices[0], 3 * sizeof(float), std::size(this->vertices),
                                &this->indices[0], std::size(this->indices), 3 * sizeof(this->indices.at(0)));

    m_geom = dCreateTriMesh(s, data, 0, 0, 0);
    dGeomSetBody(m_geom, m_body);

    //ofLog() << m_model.getMeshNames().at(0);
    //ofLog() << m_model.getMeshCount();
}

void GameObject::setPosition(glm::vec3 pos)
{
    this->pos = pos;
}

void GameObject::update()
{
    const dReal* vel = dBodyGetLinearVel(m_body);
    dBodySetLinearVel(m_body, vel[0] + accel.x, vel[1] + accel.y, vel[2] + accel.z);
}

/* Draw method collects latest data from ODE and draws the model at
 * that location/orientation.
 */
void GameObject::draw()
{
    /* Get data from ODE */
    const dReal* thePos = dBodyGetPosition(m_body);
    const dReal* oderot = dBodyGetQuaternion(m_body);

    /* Set the position */
    setPosition(glm::vec3(thePos[0],thePos[1], thePos[2]));

    /* Get ODEs rotation quaternion, convert it to an OF one,
     * and then collect the angle and vector from that: */
    m_rotation = ofQuaternion(oderot[1], oderot[2], oderot[3], oderot[0]);
    float rotationAmount;
    ofVec3f rotationAngle;
    m_rotation.getRotate(rotationAmount, rotationAngle);

    /* We can draw a transparent white box where the ODE object is, to
     * make sure that our model is being drawn approximately correctly */
    if(debug_draw) {
        ofSetColor(ofColor::black,255);
        /* Save the current state of the graphics transform stack: */
        ofPushMatrix();

        /* Translate to the correct position: */
        ofTranslate(pos.x,pos.y,pos.z);

        /* Rotate by the correct amount: */
        ofRotateDeg(rotationAmount, rotationAngle.x, rotationAngle.y, rotationAngle.z);

        /* Draw the box */
        ofDrawBox(1,1,0.1);

        /* Restore the graphics transform stack: */
        ofPopMatrix();
    }
    /* Draw the model */
    /* Save the current state of the graphics transform stack: */
    ofPushMatrix();

    /* Translate to the correct position: */
    ofTranslate(pos.x,pos.y-0.05,pos.z);

    /* Rotate by the correct amount: */
    ofRotateDeg(rotationAmount, rotationAngle.x, rotationAngle.y, rotationAngle.z);
   //model.setPosition(pos_ode[0], pos_ode[1], pos_ode[2]);

    /* Draw the model: */
    m_model.drawFaces();

    /* Restore the transformation matrix: */
    ofPopMatrix();
}
