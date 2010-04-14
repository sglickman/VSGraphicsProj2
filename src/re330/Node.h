#ifndef __Node_h__
#define __Node_h__
#include "Matrix4.h"


namespace RE330 
{
	class RE330_EXPORT Node
	{
    public:
      Matrix4 getTransformation();
      void setTransformation();
      
    protected:
      Matrix4 t;
	};
	
}

#endif

