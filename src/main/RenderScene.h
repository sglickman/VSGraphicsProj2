#ifndef RenderScene_H
#define RenderScene_H

#include "SceneManager.h"
#include <iostream>

using namespace RE330;
using namespace std;

class RenderScene
{
public:
    RenderScene() : _sm(NULL) {}
    RenderScene(SceneManager *sm) : _sm(sm) {}

    virtual void init() = 0;
    void nextFrame() {}
protected:
    SceneManager *_sm;
};

#endif
