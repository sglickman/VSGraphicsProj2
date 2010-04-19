#ifndef RobotScene_H
#define RobotScene_H

#include "RenderScene.h"
#include "Shape3D.h"

using namespace RE330;

class RobotScene : public virtual RenderScene {
public:
    RobotScene() {}
    RobotScene(SceneManager *sm) : RenderScene(sm) {}
//    ~RobotScene();
    
    void init();

protected:
    TransformGroup *teaDragon;

    Shape3D *teaShape;
    Shape3D *dragShape;
};

#endif
