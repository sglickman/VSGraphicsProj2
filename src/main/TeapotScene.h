#ifndef TeapotScene_H
#define TeapotScene_H

#include "RenderScene.h"
#include "Shape3D.h"

using namespace RE330;

class TeapotScene : public virtual RenderScene {
public:
    TeapotScene() {}
    TeapotScene(SceneManager *sm) : RenderScene(sm) {}
//    ~TeapotScene();
    
    void init();
    void nextFrame();
    Node *getRoot() {}

protected:
    TransformGroup *teaDragon;

    Shape3D *teaShape;
    Shape3D *dragShape;
};

#endif
