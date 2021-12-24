#include "physicsobject.h".h"

PhysicsObject::PhysicsObject(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, string modelName, dWorldID w, dSpaceID s)
{
    /* Set up graphics objects */
    m_model.loadModel(modelName);

    double normalizedScale = 1.0/ m_model.getNormalizedScale();
    m_model.setScale(normalizedScale * scale.x, normalizedScale * scale.y, normalizedScale * scale.z);

    this->vertices.resize(m_model.getMeshCount());
    this->indices.resize(m_model.getMeshCount());

    /* Set up physics objects */
    dMatrix3 R;
    dRFromEulerAngles(R, glm::radians(rot.x), glm::radians(rot.y), glm::radians(rot.z));
    dQuaternion Q;
    dRtoQ(R, Q);
    m_body = dBodyCreate(w);
    dBodySetPosition(m_body, pos.x, pos.y, pos.z);
    dBodySetQuaternion(m_body, Q);

    glm::mat4 transformMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale.x, scale.y, scale.z));

    for (int i = 0; i < 1; i++)
    {
        this->vertices.at(i) = m_model.getMesh(i).getVertices();
        this->indices.at(i) = m_model.getMesh(i).getIndices();

        for (auto& vec : this->vertices.at(i)) vec = transformMatrix * glm::vec4(vec, 1.f);

        dTriMeshDataID data = dGeomTriMeshDataCreate();
        dGeomTriMeshDataBuildSingle(data, &this->vertices.at(i).at(0), 3 * sizeof(float), std::size(this->vertices.at(i)),
                                    &this->indices.at(i).at(0), std::size(this->indices.at(i)), 3 * sizeof(this->indices.at(0).at(0)));

        m_geom = dCreateTriMesh(s, data, 0, 0, 0);
        ofLog() << m_model.getMeshNames().at(i);
    }

    //dGeomSetRotation(m_geom, R);
    dGeomSetBody(m_geom, m_body);

    ofLog() << m_model.getMeshCount();
}

void PhysicsObject::update()
{
}


/* Draw method collects latest data from ODE and draws the model at
 * that location/orientation.
 */

void PhysicsObject::draw()
{
    /* Get data from ODE */
    const dReal* odepos = dBodyGetPosition(m_body);
    const dReal* oderot = dBodyGetQuaternion(m_body);

    /* Set the position */
    auto pos = glm::vec3(odepos[0], odepos[1], odepos[2]);

    m_rotation = ofQuaternion(oderot[1], oderot[2], oderot[3], oderot[0]);
    float rotationAmount;
    ofVec3f rotationAngle;
    m_rotation.getRotate(rotationAmount, rotationAngle);
    m_model.setRotation(0, rotationAmount, rotationAngle.x, rotationAngle.y, rotationAngle.z);
    m_model.setPosition(pos.x, pos.y, pos.z);

    /* Draw the model: */
    m_model.drawFaces();

    /* We can draw a transparent white box where the ODE object is, to
     * make sure that our model is being drawn approximately correctly */
    if(debug_draw) {
        ofSetColor(ofColor::black,255);
        /* Save the current state of the graphics transform stack: */
        ofPushMatrix();

        /* Translate to the correct position: */
        ofTranslate(pos.x,pos.y,pos.z);

        /* Rotate by the correct amount: */
        //ofRotateDeg(rotationAmount, rotationAngle.x, rotationAngle.y, rotationAngle.z);

        /* Draw the box */
        ofDrawBox(1,1,0.1);

        /* Restore the graphics transform stack: */
        ofPopMatrix();
    }

}
