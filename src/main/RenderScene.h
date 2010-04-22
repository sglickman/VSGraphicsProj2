#ifndef RenderScene_H
#define RenderScene_H

#include "SceneManager.h"
#include <iostream>
#include "Node.h"

using namespace RE330;
using namespace std;

class RenderScene
{
public:
    RenderScene() : sceneManager(NULL) {}
    RenderScene(SceneManager *sm) : sceneManager(sm) {}

    virtual void init() = 0;
    virtual void nextFrame() = 0;
    virtual Node *getRoot() = 0;
protected:
    SceneManager *sceneManager;
};

#endif
