#include "utils.h"

namespace Utils {
float moveTowards(float start, float end, float maxAccel)
{
    if (abs(end - start) <= maxAccel)
        return end;
    else
        return start + glm::sign(end - start) * maxAccel;
}

float dirToAngle(glm::vec2 dir)
{
    float angle = glm::degrees(acos(dir.y));
    if (dir.x >= 0)
        return angle;
    else
        return 360 - angle;
}
}
