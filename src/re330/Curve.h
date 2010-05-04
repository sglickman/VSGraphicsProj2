#ifndef __Curve_h__
#define __Curve_h__

#include <vector>
#include "Vector3.h"

using namespace std;

namespace RE330
{
    class RE330_EXPORT Curve
    {
    public:
        Curve() {}
        virtual const Vector3& interpolate_point(const float t) const = 0;
        virtual const Vector3 &interpolate_deriv(const float t) const = 0;
    };

    class RE330_EXPORT CubicCurve : public virtual Curve
    {
    public:
        inline CubicCurve(const Vector3 &a, const Vector3 &b, 
                          const Vector3 &c, const Vector3 &d) : Curve()
            { p[0] = a; p[1] = b; p[2] = c; p[3] = d; }
        CubicCurve(const CubicCurve &c)
            { p[0] = c.p[0]; p[1] = c.p[1]; p[2] = c.p[2]; p[3] = c.p[3]; }

        CubicCurve& operator= (const CubicCurve& c) 
            { p[0] = c.p[0]; p[1] = c.p[1]; p[2] = c.p[2]; p[3] = c.p[3];
                return *this; }

        const Vector3& operator[] (const int i) const { return p[i]; }
        Vector3& operator[] (const int i) {return p[i]; }

        const Vector3 &interpolate_point (const float t) const;
        const Vector3 &interpolate_deriv (const float t) const;
    protected:
        Vector3 p[4];
    };

    class RE330_EXPORT PiecewiseCurve : public virtual Curve
    {
    public:
        PiecewiseCurve(const CubicCurve &c) :
            p(), nPoints(4)
            { for (int i = 0; i < 4; i++) p.push_back(c[i]); }
        PiecewiseCurve(const PiecewiseCurve &c) :
            p(c.p), nPoints(c.nPoints) {}
        PiecewiseCurve(const vector<Vector3> &points) :
            p(points), nPoints(p.size() - (p.size() - 1)%3) {}

        PiecewiseCurve& operator= (const PiecewiseCurve& c) { 
            p = c.p; 
            return *this; }

        const Vector3 &interpolate_point (const float t) const;
        const Vector3 &interpolate_deriv (const float t) const;
    protected:
        vector<Vector3> p;
        int nPoints;
    };
}

#endif /* __Curve_h__ */
