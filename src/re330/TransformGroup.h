#ifndef __TransformGroup_h__
#define __TransformGroup_h__
#include "Group.h"

namespace RE330 
{
	class RE330_EXPORT TransformGroup : Group
	{
    public:
        void light(RenderContext *r, Matrix4 *C);
        void draw(RenderContext *r, Matrix4 *C);
	};
	
}

#endif

