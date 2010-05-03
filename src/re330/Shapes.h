#ifndef __Shapes_h__
#define __Shapes_h__

#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "Object.h"
#include "SceneManager.h"
#include "Curve.h"


namespace RE330
{
    class RE330_EXPORT ObjectShape : public Object
    {
        protected:
            
        public:
            void setupObject(int nVerts, int nIndices, 
                             float* v, float* n, int* i);
    };

    class RE330_EXPORT ObjectSphere : public ObjectShape {
    public:
        ObjectSphere(const float height, const int slices, const int points);
    };

    class RE330_EXPORT ObjectBox : public ObjectShape {
    public:
        ObjectBox(const float height, const float width, const float depth);
    };
        
    class RE330_EXPORT RevolutionSurface : public ObjectShape {   
    public:
        RevolutionSurface(Curve &c, const int ncuts);
    protected:
        Curve curve;
    };
}

#endif
