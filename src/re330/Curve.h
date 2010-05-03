#ifndef __Curve_h__
#define __Curve_h__

#include <vector>
#include "Vector4.h"

using namespace std;

namespace RE330
{
    class RE330_EXPORT Curve
    {
    public:
        Curve() {}
        virtual Vector4& interpolate(const float t) const;

    };

    class RE330_EXPORT CubicCurve : public virtual Curve
    {
    public:
        CubicCurve(const Vector4 &a, const Vector4 &b, 
                   const Vector4 &c, const Vector4 &d)
            { p[0] = a; p[1] = b; p[2] = c; p[3] = d; }
        CubicCurve(const CubicCurve &c)
            { p[0] = c.p[0]; p[1] = c.p[1]; p[2] = c.p[2]; p[3] = c.p[3]; }

        CubicCurve& operator= (const CubicCurve& c) 
            { p[0] = c.p[0]; p[1] = c.p[1]; p[2] = c.p[2]; p[3] = c.p[3];
                return *this; }

        const Vector4& operator[] (const int i) const { return p[i]; }
        Vector4& operator[] (const int i) {return p[i]; }

        Vector4 &interpolate (const float t) const;
    protected:
        Vector4 p[4];
    };

    class RE330_EXPORT PiecewiseCurve : public virtual Curve
    {
    public:
        PiecewiseCurve(const CubicCurve &c) :
            p()
            { for (int i = 0; i < 4; i++) p.push_back(c[i]); }
        PiecewiseCurve(const PiecewiseCurve &c) :
            p(c.p) {}

        PiecewiseCurve& operator= (const PiecewiseCurve& c) { p = c.p; 
            return *this; }

        Vector4 &interpolate (const float t) const;
    protected:
        vector<Vector4> p;
    };
}

#endif /* __Curve_h__ */
