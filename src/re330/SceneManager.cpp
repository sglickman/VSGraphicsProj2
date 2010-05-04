#include "SceneManager.h"
#include "RenderContext.h"

#include <iostream>

using namespace std;
using namespace RE330;

SceneManager::SceneManager()
	: mCamera(0), sceneRoot(0)
{
    culling = true;
    worldRoot = new TransformGroup();

    // redLight is a red spot light.
    // whiteLight is a white directional light.
    Light* whiteLight = new Light();

    whiteLight->setAllColors(Vector3(.7, 0.7, 0.7),
                             Vector3(1.0, 1.0, 1.0),
                             Vector3(0.1, 0.1, 0.1));
    whiteLight->makeDirectional(Vector3(0.f, 0.f, 1.f));  
    worldRoot->addChild(whiteLight);
}

SceneManager::~SceneManager()
{
	if(mCamera)
	{
//		delete mCamera;
	}
    if(sceneRoot)
    {
//        delete sceneRoot;
    }
}

Object* SceneManager::createObject()
{	
    // Creates an object in the root of the scene.
	Object *o = new Object();
//	mObjectList.push_back(o);
    worldRoot->addChild(new Shape3D(o, 0));

	return o;
}

Camera* SceneManager::createCamera()
{
	mCamera = new Camera();
	return mCamera;
}

void SceneManager::setScene(Node *n) {
    sceneRoot = n;
}

void SceneManager::addChild(Node *n) {
    addChildToWorld(n);
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

        //First prepare the world's lights, then draw the objects.
        worldRoot->light(renderContext, v);
        sceneRoot->light(renderContext, v);

        worldRoot->draw(renderContext, v, mCamera->getProjectionMatrix(), culling);
        sceneRoot->draw(renderContext, v, mCamera->getProjectionMatrix(), culling);

		renderContext->endFrame();
	}
}
