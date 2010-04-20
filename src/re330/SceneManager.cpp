#include "SceneManager.h"
#include "RenderContext.h"

#include <iostream>

using namespace std;
using namespace RE330;

SceneManager::SceneManager()
	: mCamera(0)
{
    sceneRoot = new TransformGroup();
    worldRoot = new TransformGroup();

    sceneRoot->addChild(worldRoot);

    // redLight is a red spot light.
    // whiteLight is a white directional light.
    Light* whiteLight = new Light();

    whiteLight->setAllColors(Vector3(.7, 0.7, 0.7),
                             Vector3(1.0, 1.0, 1.0),
                             Vector3(0.1, 0.1, 0.1));
    whiteLight->makeDirectional(Vector3(0.f, 0.f, 1.f));  
    sceneRoot->addChild(whiteLight);
}

SceneManager::~SceneManager()
{
	if(mCamera)
	{
		delete mCamera;
	}
    if(sceneRoot)
    {
        delete sceneRoot;
    }
}

Object* SceneManager::createObject()
{	
    // Creates an object in the root of the scene.
	Object *o = new Object();
//	mObjectList.push_back(o);
    sceneRoot->addChild(new Shape3D(o, 0));

	return o;
}

Camera* SceneManager::createCamera()
{
	mCamera = new Camera();
	return mCamera;
}

void SceneManager::addChild(Node *n) {
    addChildToWorld(n);
}

void SceneManager::addChildToScene(Node *n) {
    sceneRoot->addChild(n);
}

void SceneManager::addChildToWorld(Node *n) {
    worldRoot->addChild(n);
}

void SceneManager::renderScene()
{
	GLRenderContext* renderContext = GLRenderContext::getSingletonPtr();

	if(mCamera!=0) 
	{
		renderContext->beginFrame();

		renderContext->setProjectionMatrix(mCamera->getProjectionMatrix());
		Matrix4 v = mCamera->getViewMatrix();

        //First prepare the scene's lights, then draw the objects.
        sceneRoot->light(renderContext, v);
        sceneRoot->draw(renderContext, v);

		renderContext->endFrame();
	}
}
