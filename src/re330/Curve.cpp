#include "Curve.h"
#include <iostream>

using namespace std;
using namespace RE330;

const Vector4 &CubicCurve::interpolate(const float t) const {
    return ((p[0] * p[0][3] * ((1-t)*(1-t)*(1-t)) +
             p[1] * p[1][3] * ((1-t)*(1-t)*t) +
             p[2] * p[2][3] * ((1-t)*t*t) +
             p[3] * p[3][3] * (t*t*t)) / 
            (p[0][3] + p[1][3] + p[2][3] + p[3][3]));
}

const Vector4 &PiecewiseCurve::interpolate(const float t) const {
    float big_t = ((nPoints - 1) / 3) * t; // num curves * t
    //cout << "t = " << t;

    // If we want an endpoint, just give it out
    if (t >= 1) {
        return p[nPoints-1];
    } else if (t <= 0) {
        return p[0];
    } else {
        // Determine which segment to interpolate
        int curve_i = (int)t;

        // Have the cubic curve segment interpolate itself
        return CubicCurve(p[curve_i],
                          p[curve_i + 1],
                          p[curve_i + 2],
                          p[curve_i + 3]).interpolate(t - curve_i);
    }
}
