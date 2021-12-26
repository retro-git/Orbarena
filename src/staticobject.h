#include "ode/ode.h"
#include "ofApp.h"
#include "ofCamera.h"
#include "playerobject.h"

#ifndef STATICOBJECT_H
#define STATICOBJECT_H

class StaticObject : public GameObject {
public:
    StaticObject(glm::vec3 pos,
        glm::vec3 rot,
        glm::vec3 scale,
        string modelName,
        dWorldID w,
        dSpaceID s);

    void update() override;
    void draw() override;
    void init(glm::vec3 pos,
        glm::vec3 rot,
        glm::vec3 scale,
        string modelName,
        dWorldID w,
        dSpaceID s) override;
};

#endif // STATICOBJECT_H
