#include "Curve.h"


Vector4 &CubicCurve::interpolate(const float t) const {
    return ((p[0] * p[0][3] * ((1-t)*(1-t)*(1-t)) +
             p[1] * p[1][3] * ((1-t)*(1-t)*t) +
             p[2] * program[2][3] * ((1-t)*t*t) +
             p[3] * p[3][3] *(t*t*t)) / 
            (p[0][3] + p[1][3] + p[2][3] + p[3][3]));
}
