#include "Curve.h"
#include <iostream>

using namespace std;
using namespace RE330;

const Vector3 &CubicCurve::interpolate_point(const float t) const {
    return ((p[0] * p[0][2] * ((1-t)*(1-t)*(1-t)) +
             p[1] * p[1][2] * ((1-t)*(1-t)*t) +
             p[2] * p[2][2] * ((1-t)*t*t) +
             p[3] * p[3][2] * (t*t*t)) / 
            (p[0][2] + p[1][2] + p[2][2] + p[3][2]));
}
const Vector3 &CubicCurve::interpolate_deriv(const float t) const {
    return ((p[0] * p[0][2] * (-3*(1-t)*(1-t)) +
             p[1] * p[1][2] * ((1-t)*(1-t) - 2*t*(1-t)) +
             p[2] * p[2][2] * ((1-t)*t*2 - t*t) +
             p[3] * p[3][2] * (3*t*t)) / 
            (p[0][2] + p[1][2] + p[2][2] + p[3][2]));
}

const Vector3 &PiecewiseCurve::interpolate_point(const float t) const {
    float big_t = ((nPoints - 1.0) / 3.0) * t; // num curves * t
    //cout << "t = " << t;

    // If we want an endpoint, just give it out
    if (t >= 1) {
        return p[nPoints-1];
    } else if (t <= 0) {
        return p[0];
    } else {
        // Determine which segment to interpolate
        int curve_i = (int)big_t;

        // Have the cubic curve segment interpolate itself
        return CubicCurve(p[curve_i*3],
                          p[curve_i*3 + 1],
                          p[curve_i*3 + 2],
                          p[curve_i*3 + 3]).interpolate_point(big_t - curve_i);
    }
}
const Vector3 &PiecewiseCurve::interpolate_deriv(const float t) const {
    float big_t = ((nPoints - 1) / 3) * t; // num curves * t
    //cout << "t = " << t;

    // If we want an endpoint, just give it out
    if (t >= 1) {
        return p[nPoints-1]-p[nPoints-2];
    } else if (t <= 0) {
        return p[0]-p[1];
    } else {
        // Determine which segment to interpolate
        int curve_i = (int)big_t;
        cout << "curve_i" << curve_i << "   ";

        // Have the cubic curve segment interpolate itself
        return CubicCurve(p[curve_i*3],
                          p[curve_i*3 + 1],
                          p[curve_i*3 + 2],
                          p[curve_i*3 + 3]).interpolate_deriv(big_t - curve_i);
    }
}

