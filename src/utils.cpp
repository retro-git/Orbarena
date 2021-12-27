#include "utils.h"
#include "ofApp.h"

namespace Utils {
float moveTowards(float start, float end, float maxAccel)
{
    if (abs(end - start) <= maxAccel)
        return end;
    else
        return start + glm::sign(end - start) * maxAccel;
}
}
