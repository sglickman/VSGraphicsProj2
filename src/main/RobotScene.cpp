#include "RobotScene.h"
#include "ObjReader.h"
#include "Shapes.h"

#include <math.h>

// RobotScene::~RobotScene() {

// }

void RobotScene::init() {
    // Prepare the shader
    Shader *shader = new Shader("src/Shaders/diffuse_shading.vert",
                                "src/Shaders/diffuse_shading.frag");
    shader->use();

    // Temporary object, materials
    Object *obj;
    Material *robomat, *mat;
    robomat = new Material();
    robomat->setSpecular(Vector3(1, 1, 1));
    robomat->setShininess(40.f);
    robomat->setDiffuse(Vector3(.5, .7, 1.f));
    robomat->setAmbient(Vector3(.1, .1, .1));
    
    // Set up the robot scene tree hierarchy
    theRobot = new TransformGroup();

    // Create the Robot's head.
    obj = Shapes::createSphere(.2f, 10, 10);
    mat = new Material(*robomat);

    head = new Shape3D(obj, mat);
    head->applyTransformation(Matrix4::translate(0, .5, 0));
    theRobot->addChild(head);

    // Create the rest of the Robot.
    robotBody = new TransformGroup();

    // Create the Robot's torso. Change to some other shape later.
    obj = Shapes::createBox(1, 1, 1);
    mat = new Material(*robomat);
    
    torso = new Shape3D(obj, mat);    
    robotBody->addChild(torso);
    
    // Create the Robot's left arm.
    leftArm = new TransformGroup();

    // Create the Robot's left shoulder.
    obj = Shapes::createSphere(.1f, 10, 10);
    mat = new Material(*robomat);
    
    leftShoulder = new Shape3D(obj, mat);
    leftShoulder->applyTransformation(Matrix4::translate(0, 0, 0));
    leftArm->addChild(leftShoulder);

    // Create the Robot's left hand.
    obj = Shapes::createSphere(.1f, 10, 10);
    mat = new Material(*robomat);
    
    leftHand = new Shape3D(obj, mat);
    leftHand->applyTransformation(Matrix4::translate(0, -.5, 0));
    leftArm->addChild(leftHand);

    leftArm->applyTransformation(Matrix4::translate(-.4, .3, 0));
    robotBody->addChild(leftArm);

    // Create the Robot's right arm.
    rightArm = new TransformGroup();

    // Create the Robot's right shoulder.
    obj = Shapes::createSphere(.1f, 10, 10);
    mat = new Material(*robomat);
    
    rightShoulder = new Shape3D(obj, mat);
    rightShoulder->applyTransformation(Matrix4::translate(0, 0, 0));
    rightArm->addChild(rightShoulder);

    // Create the Robot's right hand.
    obj = Shapes::createSphere(.1f, 10, 10);
    mat = new Material(*robomat);

    rightHand = new Shape3D(obj, mat);
    rightHand->applyTransformation(Matrix4::translate(0, -.5, 0));
    rightArm->addChild(rightHand);

    rightArm->applyTransformation(Matrix4::translate(.4, .3, 0));
    //robotBody->addChild(rightArm);

    // Create the Robot's left leg.
    leftLeg = new TransformGroup();

    // Create the Robot's lower left leg.
    leftLowerLeg = new TransformGroup();

    // Create the Robot's left knee.
    obj = Shapes::createSphere(.1f, 10, 10);
    mat = new Material(*robomat);

    leftKnee = new Shape3D(obj, mat);
    leftLowerLeg->addChild(leftKnee);
    
    leftLowerLeg->applyTransformation(Matrix4::translate(0, -.5, 0));
    leftLeg->addChild(leftLowerLeg);

    leftLeg->applyTransformation(Matrix4::translate(-.2, -.5, 0));
    robotBody->addChild(leftLeg);

    // Create the Robot's right leg.
    rightLeg = new TransformGroup();

    // Create the Robot's lower right leg.
    rightLowerLeg = new TransformGroup();

    // Create the Robot's right knee.
    obj = Shapes::createSphere(.1f, 10, 10);
    mat = new Material(*robomat);

    rightKnee = new Shape3D(obj, mat);
    rightLowerLeg->addChild(rightKnee);
    
    rightLowerLeg->applyTransformation(Matrix4::translate(0, -.5, 0));
    rightLeg->addChild(rightLowerLeg);

    rightLeg->applyTransformation(Matrix4::translate(.2, -.5, 0));
    robotBody->addChild(rightLeg);

    theRobot->addChild(robotBody);

    theRobot->applyTransformation(Matrix4::translate(0, .3, 0));
    sceneManager->addChild(theRobot);
    

}

void RobotScene::nextFrame() {
    static int f = 1;
    rightArm->applyTransformation(Matrix4::rotateX(0.04f * cos(f/20.0)));
    leftArm->applyTransformation(Matrix4::rotateX(-0.04f * cos(f/20.0)));
    f++;
    //theRobot->applyTransformation(Matrix4::rotateY(-0.01f));
}
