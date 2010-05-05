#include "Curve.h"
#include <iostream>

using namespace std;
using namespace RE330;

const Vector3 &CubicCurve::interpolate_point(const float t) const {
    Vector3 a = p[0]*-1 + p[1]*3 + p[2]*-3 + p[3];
    Vector3 b = p[0]*3 + p[1]*-6 + p[2]*3;
    Vector3 c = p[0]*-3 + p[1]*3;
    Vector3 d = p[0];
    
    return (a *(t*t*t) + b *(t*t) + c *t + d);
    // return ((p[0] * p[0][2] * ((1-t)*(1-t)*(1-t)) +
    //          p[1] * p[1][2] * 3 * ((1-t)*(1-t)*t) +
    //          p[2] * p[2][2] * 3 * ((1-t)*t*t) +
    //          p[3] * p[3][2] * (t*t*t)) / 
    //         (p[0][2] * ((1-t)*(1-t)*(1-t)) + 
    //          p[1][2] * 3 * ((1-t)*(1-t)*t) +
    //          p[2][2] * 3 * ((1-t)*t*t) +
    //          p[3][2] * (t*t*t)));
}
const Vector3 &CubicCurve::interpolate_deriv(const float t) const {
    Vector3 a = p[0]*-1 + p[1]*3 + p[2]*-3 + p[3];
    Vector3 b = p[0]*3 + p[1]*-6 + p[2]*3;
    Vector3 c = p[0]*-3 + p[1]*3;
    
    return (a *(3*t*t) + b *(2*t) + c);
    // float denom = (
    //  p[0][2] * (-3*(1-t)*(1-t)) +
    //  p[1][2] * 3 * ((1-t)*(1-t) - 2*t*(1-t)) +
    //  p[2][2] * 3 * ((1-t)*t*2 - t*t) +
    //  p[3][2] * (3*t*t));
    // if (denom == 0) {
    //     printf("weight 1: %f, weight 2: %f, weight 3: %f, weight 4: %f, t: %f\n",
    //     p[0][2],
    //     p[1][2],
    //     p[2][2],
    //     p[3][2],
    //     t);
    // }
    // 
    // printf("denom = %f\n", denom);
    // return ((p[0] * p[0][2] * (-3*(1-t)*(1-t)) +
    //          p[1] * p[1][2] * 3 * ((1-t)*(1-t) - 2*t*(1-t)) +
    //          p[2] * p[2][2] * 3 * ((1-t)*t*2 - t*t) +
    //          p[3] * p[3][2] * (3*t*t)) / 
    //         (
    //          p[0][2] * (-3*(1-t)*(1-t)) +
    //          p[1][2] * 3 * ((1-t)*(1-t) - 2*t*(1-t)) +
    //          p[2][2] * 3 * ((1-t)*t*2 - t*t) +
    //          p[3][2] * (3*t*t))
    //         );
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
        return p[1]-p[0];
    } else {
        // Determine which segment to interpolate
        int curve_i = (int)big_t;
        // cout << "curve_i" << curve_i << "   ";

        // Have the cubic curve segment interpolate itself
        return CubicCurve(p[curve_i*3],
                          p[curve_i*3 + 1],
                          p[curve_i*3 + 2],
                          p[curve_i*3 + 3]).interpolate_deriv(big_t - curve_i);
    }
}

