#ifndef __Node_h__
#define __Node_h__
#include "Matrix4.h"


namespace RE330 
{
	class RE330_EXPORT Node
	{
    public:
        Matrix4 *getTransformation() { return &t; }
        void setTransformation(Matrix4* _t) { t = *_t; };
      
    protected:
        Matrix4 t;
	};
	
}

#endif

