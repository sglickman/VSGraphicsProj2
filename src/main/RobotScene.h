#ifndef RobotScene_H
#define RobotScene_H

#include "RenderScene.h"
#include "Shape3D.h"
#include "Light.h"

using namespace RE330;

class RobotScene : public virtual RenderScene {
public:
    RobotScene() {}
    RobotScene(SceneManager *sm) : RenderScene(sm) {}
//    ~RobotScene();
    
    void init();
    void nextFrame();
    Node* getRoot() {return everything;}

protected:
    TransformGroup *everything;
    TransformGroup *theRobot, *robotBody;
    TransformGroup *leftArm, *leftLeg, *leftLowerLeg;
    TransformGroup *rightArm, *rightLeg, *rightLowerLeg;

    Light *flashlight;

    Shape3D *theGround;
    Shape3D *head, *torso;
    Shape3D *leftShoulder, *leftArmPart, *leftHand;
    Shape3D *rightShoulder, *rightArmPart, *rightHand;
    Shape3D *leftThigh, *leftKnee, *leftLegPart, *leftFoot;
    Shape3D *rightThigh, *rightKnee, *rightLegPart, *rightFoot;
    Shape3D * tpot;
};

#endif
