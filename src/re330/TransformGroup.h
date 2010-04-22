#ifndef __TransformGroup_h__
#define __TransformGroup_h__
#include "Group.h"

namespace RE330 
{
	class RE330_EXPORT TransformGroup : public Group
	{
    public:
        void light(RenderContext *r, const Matrix4 &C);
        void draw(RenderContext *r, const Matrix4 &C, const Matrix4 &P);
	};
	
}

#endif

