#include "ofApp.h"
#ifndef QUEUEOBJSTRUCT_H
#define QUEUEOBJSTRUCT_H

struct QueueObjStruct {
    ObjectType type;
    glm::vec3 pos;
    glm::vec3 rot;
    glm::vec3 scale;
    string modelName;
    dWorldID w;
    dSpaceID s;
};

#endif // QUEUEOBJSTRUCT_H
