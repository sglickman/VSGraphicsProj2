#ifndef __Object_h__
#define __Object_h__

#include "RE330_global.h"
#include "VertexData.h"
#include "Matrix4.h"
#include "Material.h"

namespace RE330 
{
	/** This class provides an abstraction of scene objects.
        @remarks
		The SceneManager creates and deletes objects. Vertex data is stored
		in the VertexData member.
	*/
	class RE330_EXPORT Object
	{
	public:
        Object() {}
		VertexData vertexData;
	};

}

#endif

