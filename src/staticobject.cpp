#include "staticobject.h"
#include "ode/ode.h"

StaticObject::StaticObject(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, string modelName, dWorldID w, dSpaceID s)
{
    /* Set up graphics objects */
    m_model.loadModel(modelName);

    double normalizedScale = 1.0/ m_model.getNormalizedScale();
    m_model.setScale(normalizedScale * scale.x, normalizedScale * scale.y, normalizedScale * scale.z);
    //m_model.setRotation(0,rot.x,1,0,0);
    //m_model.setRotation(1,rot.y,0,1,0);
    //m_model.setRotation(2,rot.z,0,0,1);
    //m_model.setPosition(pos.x, pos.y, pos.z);

    this->vertices.resize(m_model.getMeshCount());
    this->indices.resize(m_model.getMeshCount());

    dMatrix3 R;
    dRFromEulerAngles(R, glm::radians(rot.x), glm::radians(rot.y), glm::radians(rot.z));
    dQuaternion Q;
    dRtoQ(R, Q);

    glm::mat4 transformMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale.x, scale.y, scale.z));

    for (int i = 0; i < m_model.getMeshCount(); i++)
    {
        this->vertices.at(i) = m_model.getMesh(i).getVertices();
        this->indices.at(i) = m_model.getMesh(i).getIndices();

        for (auto& vec : this->vertices.at(i)) vec = transformMatrix * glm::vec4(vec, 1.f);

        dTriMeshDataID data = dGeomTriMeshDataCreate();
        dGeomTriMeshDataBuildSingle(data, &this->vertices.at(i).at(0), 3 * sizeof(float), std::size(this->vertices.at(i)),
                                    &this->indices.at(i).at(0), std::size(this->indices.at(i)), 3 * sizeof(this->indices.at(0).at(0)));

        m_geom = dCreateTriMesh(s, data, 0, 0, 0);
        dGeomSetPosition(m_geom, pos.x, pos.y, pos.z);
        dGeomSetQuaternion(m_geom, Q);
    }

    ofLog() << __func__;
    ofLog() << m_model.getMeshNames().at(0);
    ofLog() << m_model.getMeshCount();
}

void StaticObject::update()
{

}

void StaticObject::draw()
{
    /* Get data from ODE */
    const dReal* odepos = dGeomGetPosition(m_geom);
    dQuaternion oderot;
    dGeomGetQuaternion(m_geom, oderot);

    /* Set the position */
    auto pos = glm::vec3(odepos[0], odepos[1], odepos[2]);

    m_rotation = ofQuaternion(oderot[1], oderot[2], oderot[3], oderot[0]);
    float rotationAmount;
    ofVec3f rotationAngle;
    m_rotation.getRotate(rotationAmount, rotationAngle);
    m_model.setRotation(0, rotationAmount, rotationAngle.x, rotationAngle.y, rotationAngle.z);
    m_model.setPosition(pos.x, pos.y, pos.z);

    ofPushMatrix();

    ofRotateDeg(-180, 0, 0, 1);
    m_model.drawFaces();

    ofPopMatrix();
}
