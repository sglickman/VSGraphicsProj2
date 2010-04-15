#ifndef __Node_h__
#define __Node_h__

#include "Matrix4.h"
#include "RenderContext.h"
#include <iostream>
using namespace std;

namespace RE330 
{
	class RE330_EXPORT Node
	{
    public:
        Node() : t(&Matrix4(Matrix4::IDENTITY)) {}
        ~Node() { if(t != 0) { delete t; } }

        virtual void light(RenderContext *r, Matrix4 *C) = 0;
        virtual void draw(RenderContext *r, Matrix4 *C) = 0;

        Matrix4 *getTransformation() { return t; }
        void setTransformation(Matrix4* _t) { t = _t; };
      
    protected:
        Matrix4 *t;
	};
	
}

#endif

