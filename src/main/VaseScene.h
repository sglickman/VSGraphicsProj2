#ifndef VaseScene_H
#define VaseScene_H

#include "RenderScene.h"
#include "Matrix4.h"
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
    Shape3D *donut;
    Shape3D *vase;
    Shape3D *coke;
    Shape3D *apple;
    Shape3D *table;
    Shape3D *leftCandle;
    Shape3D *rightCandle;
};

#endif