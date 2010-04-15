#ifndef __SceneManager_h__
#define __SceneManager_h__

#include "RE330_global.h"
#include "Camera.h"
#include "Object.h"
#include "RenderContext.h"
#include "GLRenderContext.h"
#include <list>
#include <stdlib.h>
#include <time.h>

#include "Light.h"
#include "Group.h"
#include "Shape3D.h"

using namespace std;

namespace RE330 
{
	/** This class provides an abstraction of a scene. It manages a camera,
		objects in the scene, etc. It is the main interface for applications
		to the rendering engine.
	*/
	class RE330_EXPORT SceneManager
	{
        friend class Shapes;
	public:
		SceneManager();
		~SceneManager();

		/** This method creates a default camera.
		*/
		Camera *createCamera();

		/** This method creates an object and adds it to the list of object
			stored in the scene manager.
		*/
		Object *createObject();
        // Create object no longer should be used, now with the tree hierarchy

        /** Add a node to the root node.
         */
        void addChild(Node *n);

		/** This method needs to be called in the renderSceneEvent
			event handler of the RenderWidget. 
		@remarks
			You should *not* call this anywhere else in your code except in 
			the renderScene event handler of your RenderWidget. To trigger 
			rendering, call updateScene of your RenderWidget, which will then 
			trigger the renderScene event handler to be called. 
		*/
		void renderScene();

	private:
		Camera *mCamera;
        Group *sceneRoot;
	};

}

#endif
