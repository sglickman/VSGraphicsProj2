#include "Curve.h"
#include <iostream>

using namespace std;
using namespace RE330;

const Vector3 &CubicCurve::interpolatePoint(const float t) const {
    return (a *(t*t*t) + b *(t*t) + c *t + d);
}
const Vector3 &CubicCurve::interpolateDeriv(const float t) const {
    return (a *(3*t*t) + b *(2*t) + c);
}

void CubicCurve::updatePolynomial() {
    a = p[0]*-1 + p[1]*3 + p[2]*-3 + p[3];
    b = p[0]*3 + p[1]*-6 + p[2]*3;
    c = p[0]*-3 + p[1]*3;
    d = p[0];
}

const Vector3 &PiecewiseCurve::interpolatePoint(const float t) const {
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
        return subCurves[curve_i].interpolatePoint(big_t - curve_i);
    }
}
const Vector3 &PiecewiseCurve::interpolateDeriv(const float t) const {
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
        return subCurves[curve_i].interpolateDeriv(big_t - curve_i);
    }

}

void PiecewiseCurve::updateCurves() {
    subCurves = vector<CubicCurve>();
    for (int i = 0; i < (nPoints-1)/3; i++) {
        subCurves.push_back(CubicCurve(p[i*3],
                                       p[i*3 + 1],
                                       p[i*3 + 2],
                                       p[i*3 + 3]));
    } 
}
