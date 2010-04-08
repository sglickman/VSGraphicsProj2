#include "SceneManager.h"
#include "RenderContext.h"

using namespace RE330;

SceneManager::SceneManager()
	: mCamera(0)
{
  Light* redLight = new Light();
  Light* blueLight = new Light();
  blueLight->setDirection(Vector3(-1, 0, 0));
  blueLight->setPosition(Vector3(10, 0, 0));
  blueLight->setSpotDirection(Vector3(-1, 0, 0));
  blueLight->setSpotCutoff(10.f);
  blueLight->setDiffuseColor(Vector3(0.0, 0.0, 1.0));
  blueLight->setAmbientColor(Vector3(0.1, 0.1, 0.2));
  blueLight->setSpecularColor(Vector3(0.0, 0.0, 1.0));
  blueLight->setType(Light::SPOT);
  redLight->setType(Light::POINT);
  redLight->setPosition(Vector3(0.f, 0.f, 20.f));
  redLight->setSpotDirection(Vector3(0.f,0.f, -1.f));
  redLight->setSpotCutoff(5.f);
  redLight->setSpotExponent(5.f);
  redLight->setDiffuseColor(Vector3(1.0, 0.0, 0.0));
  redLight->setAmbientColor(Vector3(0.2, 0.1, 0.1));
  redLight->setSpecularColor(Vector3(1.0, 0.0, 0.0));
  
  
  mLightList.push_back(blueLight);
  mLightList.push_back(redLight);
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
