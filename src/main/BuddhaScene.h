#ifndef BuddhaScene_h
#define BuddhaScene_h

#include "RenderScene.h"
#include "Shape3D.h"
#include "ObjReader.h"

using namespace RE330;

class BuddhaScene : public virtual RenderScene {
public:
    BuddhaScene() {}
    BuddhaScene(SceneManager *sm) : RenderScene(sm) {}

    void init();
    void nextFrame();

protected:
    TransformGroup *booDahRay;
    Shape3D **daBooDahs;
};

#endif
