#include "SceneManager.h"
#include "RenderContext.h"

using namespace RE330;

SceneManager::SceneManager()
	: mCamera(0)
{
  
  // redLight is a red spot light.
  // whiteLight is a white directional light.
  Light* whiteLight = new Light();
  Light* redLight = new Light();
  redLight->setPosition(Vector3(0.f, 0, 2));
  redLight->setSpotDirection(Vector3(0, 0, -1));
  redLight->setSpotCutoff(7.f);
  redLight->setDiffuseColor(Vector3(1.0, .0, .0));
  redLight->setAmbientColor(Vector3(0.1, 0.1, 0.1));
  redLight->setSpecularColor(Vector3(.2, .2, .2));
  redLight->setType(Light::SPOT);
  whiteLight->setType(Light::DIRECTIONAL);
  whiteLight->setDirection(Vector3(-1.f, 0.f, 0.f));
  whiteLight->setDiffuseColor(Vector3(.7, 0.7, 0.7));
  whiteLight->setAmbientColor(Vector3(0.1, 0.1, 0.1));
  whiteLight->setSpecularColor(Vector3(1.0, 1.0, 1.0));
  
  
  mLightList.push_back(redLight);
  mLightList.push_back(whiteLight);
}

SceneManager::~SceneManager()
{
	if(mCamera)
	{
		delete mCamera;
	}
	while(mObjectList.size() > 0)
	{
		Object *o = mObjectList.front();
	    mObjectList.pop_front();
		delete o;
	} 
	while(mLightList.size() > 0)
	{
    Light *l = mLightList.front();
    mLightList.pop_front();
    delete l;
	}
}

Object* SceneManager::createObject()
{	
	Object *o = new Object();
	mObjectList.push_back(o);

	return o;
}

Camera* SceneManager::createCamera()
{
	mCamera = new Camera();
	return mCamera;
}

void SceneManager::renderScene()
{
	GLRenderContext* renderContext = GLRenderContext::getSingletonPtr();
  renderContext->setModelViewMatrix(Matrix4::IDENTITY);
  renderContext->setLights(mLightList);

	if(mCamera!=0) 
	{
		renderContext->beginFrame();

		renderContext->setProjectionMatrix(mCamera->getProjectionMatrix());
		Matrix4 v = mCamera->getViewMatrix();

		// Iterate through list of objects
		std::list<Object *>::const_iterator iter;
		for (iter=mObjectList.begin(); iter!=mObjectList.end(); iter++)
		{
			Object *o = (*iter);
			Matrix4 m = o->getTransformation();

			renderContext->setModelViewMatrix(v*m);
			renderContext->render(o);
		}

		renderContext->endFrame();
	}
}
