#ifndef VaseScene_H
#define VaseScene_H

#include "RenderScene.h"
#include "Shape3D.h"
#include "Light.h"

using namespace RE330;

class VaseScene : public virtual RenderScene {
public:
    VaseScene() {}
    VaseScene(SceneManager *sm) : RenderScene(sm) {}
//    ~VaseScene();
    
    void init();
    void nextFrame();
    Node* getRoot() {return everything;}

protected:
    TransformGroup *everything;
    Shape3D *theVase;
};

#endif
