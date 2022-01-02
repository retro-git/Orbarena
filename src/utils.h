#include "ofApp.h"

#ifndef UTILS_H
#define UTILS_H

namespace Utils {
float moveTowards(float start, float end, float maxAccel);

float dirToAngle(glm::vec2 dir);
}

#endif // UTILS_H
