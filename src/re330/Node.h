#ifndef __Node_h__
#define __Node_h__
#include "Matrix4.h"
#include "RenderContext.h"

namespace RE330 
{
	class RE330_EXPORT Node
	{
    public:
        Node() : t(&Matrix4(Matrix4::IDENTITY)) {}
        ~Node() { if(t != 0) { delete t; } }

        void light(RenderContext *r, Matrix4 *C) {}
        void draw(RenderContext *r, Matrix4 *C) {}

        Matrix4 *getTransformation() { return t; }
        void setTransformation(Matrix4* _t) { t = _t; };
      
    protected:
        Matrix4 *t;
	};
	
}

#endif

